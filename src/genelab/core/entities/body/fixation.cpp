#include "fixation.h"

// Qt
#include <QStringBuilder>
#include <QDebug>
#include <QVariantList>

// Engine
#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"

// World
#include "world/btworld.h"

// Shape
#include "body/bone.h"
#include "btshapesfactory.h"
#include "bullet/shapes/btsphere.h"

#include "entity.h"
#include "widgets/entities/fixationproperties.h"


namespace GeneLabCore {

    FixationProperties* Fixation::inspectorWidget = NULL;
    const btScalar Fixation::PERCENT_BONE_INSIDE_FIX = 0.15f;

    #define FIXATION_DENSITY 1.0f
    #define FIXATION_FRICTION 0.6f

    // --------------------------
    // -- DELEGATE CONSTRUCTOR --
    // --------------------------

    Fixation::Fixation(btShapesFactory *shapesFactory,
                       btRigidBody* body,
                       btScalar radius,
                       btTransform localFixation,
                       Bone *parentBone) {
        this->shapesFactory     = shapesFactory;
        this->rigidBody         = body;
        this->localFixation.setIdentity();
        this->localFixation     = localFixation;
        this->radius            = radius;
        this->airFixation       = NULL;
        this->parentBone        = parentBone;
        this->entity            = NULL;
        this->delegatedSetup    = true;

        this->rigidBody->setFriction(FIXATION_FRICTION); ////////////////////////////////////////// TEST
    }


    // -------------------------------
    // -- ROOT FIXATION CONSTRUCTOR --
    // -------------------------------

    Fixation::Fixation(btShapesFactory *shapesFactory,
                       btScalar radius,
                       btTransform initTransform) : QObject(),
        radius(radius), entity(NULL), airFixation(NULL), parentBone(NULL)
    {
        this->shapesFactory = shapesFactory;
        this->localFixation.setIdentity();

        sphere = shapesFactory->createSphere(radius, initTransform); // btScalar(FIXATION_DENSITY)
        this->rigidBody     = sphere->getRigidBody();
        this->rigidBody->setFriction(FIXATION_FRICTION); ////////////////////////////////////////// TEST
        delegatedSetup      = false;
    }

    // -----------
    // -- SETUP --
    // -----------

    void Fixation::setup()
    {
        if(!delegatedSetup) {

            // shape
            sphere->setup();

            // origins
            origin = new RigidBodyOrigin(RigidBodyOrigin::FIXATION,(QObject *)this);
            rigidBody->setUserPointer(origin);

            // state
            //rigidBody->setDeactivationTime(100.0);
            rigidBody->setActivationState(DISABLE_DEACTIVATION);
        }

        for(int i=0;i<bones.size();++i)
            bones.at(i)->setup();
    }

    // ----------------
    // -- DESTRUCTOR --
    // ----------------

    Fixation::~Fixation()
    {
        if(this->airFixation) {
            shapesFactory->getWorld()->getBulletWorld()->removeConstraint(airFixation);
            delete this->airFixation;
        }

        while(sensors.size()) {
            entity->removeLinksToSensor(sensors.at(0));
            delete sensors.at(0);
            sensors.removeFirst();
        }

        while(bones.size()) {
            delete bones.at(0);
            bones.removeFirst();
        }

        if(!delegatedSetup && this->origin != 0)
            delete this->origin;

        if(!delegatedSetup)
            delete sphere;
    }

    // ----------
    // -- BONE --
    // ----------

    Bone *Fixation::addBone(btScalar yAxis, btScalar zAxis,
                            btScalar boneRadius,
                            btScalar boneLength,
                            btScalar endFixRadius,
                            const btVector3 &lowerLimits,
                            const btVector3 &upperLimits) {

        btQuaternion local1;
        local1.setRotation(btVector3(0, 1, 0), yAxis);
        btQuaternion local2;
        local2.setRotation(btVector3(0, 0, 1), zAxis);
        local1 *= local2;

        btQuaternion localOrientation = local1;

        // Get the initial transform
        btTransform initTransform = this->rigidBody->getWorldTransform();

        initTransform *= localFixation;
        initTransform.setRotation(initTransform.getRotation()*localOrientation);

        btVector3 newPos(0, btScalar((boneLength*0.5 + radius)), 0);
        btVector3 transposedPos = initTransform*newPos;

        btTransform boneTransform;
        boneTransform.setIdentity();

        boneTransform.setRotation(initTransform.getRotation());
        boneTransform.setOrigin(transposedPos);

        Bone * bone = new Bone(shapesFactory, yAxis, zAxis, boneRadius, boneLength, endFixRadius, boneTransform);

        btTransform localBone;
        localBone.setIdentity();
        localBone.setOrigin(btVector3(btScalar(0.), btScalar(-bone->getLength()*0.5 - radius), btScalar(0.)));

        btTransform localFix;
        localFix.setIdentity();
        localFix.setRotation(localOrientation);
        localFix.setOrigin(localFixation.getOrigin());

        btGeneric6DofConstraint * ct = new btGeneric6DofConstraint(*this->rigidBody,*bone->getRigidBody(),
                                                               localFix, localBone, false);

        ct->setAngularLowerLimit(lowerLimits);
        ct->setAngularUpperLimit(upperLimits);
        bone->setParentConstraint(ct);
        bone->setEntity(entity);
        bones.append(bone);

        return bone;
    }


    // -------------
    // -- SENSORS --
    // -------------

    void Fixation::addSensor(Sensor * sensor)
    {
        sensors.append(sensor);

        if(entity)
            entity->addLinkToSensor(sensor);
    }

    void Fixation::removeSensor(Sensor *sensor){

        sensors.removeOne(sensor);

        if(entity)
            entity->removeLinksToSensor(sensor);
    }

    // ---------------
    // -- INSPECTOR --
    // ---------------

    FixationProperties *Fixation::getInspectorWidget()
    {
        if(inspectorWidget == NULL)
            inspectorWidget = new FixationProperties();

        inspectorWidget->setFixation(this);

        return inspectorWidget;
    }

    FixationProperties *Fixation::getEmptyInspectorWidget()
    {
        if(inspectorWidget == NULL)
            inspectorWidget = new FixationProperties();

        return inspectorWidget;
    }

    // ------------
    // -- ENTITY --
    // ------------

    void Fixation::setEntity(Entity * entity)
    {
        this->entity = entity;

        foreach(Bone *bone, bones)
            bone->setEntity(entity);
    }

    // -----------
    // -- TOOLS --
    // -----------

    void Fixation::setRadius(btScalar radius)
    {
        this->radius = radius;

        // root
        if(parentBone == NULL) {

            sphere->setRadius(radius);

            // adapt children connections
            foreach(Bone *b, bones)
            {
                b->getParentConstraint()->getFrameOffsetA().setOrigin(btVector3(btScalar(0.), btScalar(0), btScalar(0.)));
                b->getParentConstraint()->getFrameOffsetB().setOrigin(btVector3(btScalar(0.), btScalar(-b->getLength()*0.5 - radius), btScalar(0.)));
            }
        }
        else {

            // adapt parent
            parentBone->setEndFixationRadius(radius);
        }
    }

    void Fixation::setSelected(bool isSelected)
    {
        sphere->setSelected(isSelected);
    }

    void Fixation::fixeInTheAir()
    {
        // fixe root in the air
        btTransform local; local.setIdentity();
        btGeneric6DofConstraint *ct = new btGeneric6DofConstraint(*this->rigidBody,local,true);
        ct->setAngularLowerLimit(btVector3(0,0,0));
        ct->setAngularUpperLimit(btVector3(0,0,0));
        airFixation = ct;

        shapesFactory->getWorld()->getBulletWorld()->addConstraint(ct);
    }

    void Fixation::unfixInTheAir()
    {
        if(airFixation != NULL)
        {
            shapesFactory->getWorld()->getBulletWorld()->removeConstraint(airFixation);
            delete airFixation;
            airFixation = NULL;
        }
    }

    // -------------------
    // -- SERIALIZATION --
    // -------------------

    QVariant Fixation::serialize()
    {
        QVariantMap fixation;
        QVariantList bonesVariantList;
        QVariantList sensorsVariantList;

        fixation.insert("radius",QVariant((double)radius));

        foreach(Bone *bone, bones) {
            bonesVariantList.append(bone->serialize());
        }

        foreach(Sensor *sensor, this->sensors) {
            sensorsVariantList.append(sensor->serialize());
        }

        fixation.insert("bones", bonesVariantList);
        fixation.insert("sensors", sensorsVariantList);

        return fixation;
    }
}
