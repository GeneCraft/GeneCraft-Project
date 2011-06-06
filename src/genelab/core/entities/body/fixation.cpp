#include "fixation.h"

// Qt
#include <QStringBuilder>
#include <QDebug>
#include <QVariantList>

// Engine
#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"

// Shape
#include "body/bone.h"
#include "btshapesfactory.h"
#include "bullet/shapes/btsphere.h"

#include "entity.h"
#include "widgets/entities/fixationproperties.h"


namespace GeneLabCore {

    FixationProperties* Fixation::inspectorWidget = 0;
    const btScalar Fixation::PERCENT_BONE_INSIDE_FIX = 0.15f;

    #define FIXATION_DENSITY 1.0f
    #define FIXATION_FRICTION 0.6f

    Fixation::Fixation(btShapesFactory *shapesFactory,
                       btRigidBody* body,
                       btScalar radius,
                       btTransform localFixation) {
        this->shapesFactory = shapesFactory;
        this->rigidBody = body;
        this->rigidBody->setFriction(FIXATION_FRICTION); ////////////////////////////////////////// TEST
        this->localFixation.setIdentity();
        this->localFixation = localFixation;
        this->radius = radius;
        airFixation = 0;
        entity = 0;
        delegatedSetup = true; 
    }

    Fixation::Fixation(btShapesFactory *shapesFactory,
                       btScalar radius,
                       btTransform initTransform) : QObject(),
        radius(radius), entity(0), airFixation(0)
    {
        this->shapesFactory = shapesFactory;
        this->localFixation.setIdentity();

        sphere = shapesFactory->createSphere(radius, initTransform); // btScalar(FIXATION_DENSITY)
        this->rigidBody = sphere->getRigidBody();
        this->rigidBody->setFriction(FIXATION_FRICTION); ////////////////////////////////////////// TEST
        entity = 0;
        airFixation = 0;
        delegatedSetup = false;
    }

    Fixation::~Fixation()
    {
        while(bones.size())
        {
            delete bones.at(0);
            bones.removeAt(0);
        }

        delete sphere;
    }

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

    btRigidBody* Fixation::getRigidBody()
    {
        return this->rigidBody;
        //return this->rigidBody;
    }

    void Fixation::setSelected(bool isSelected)
    {
        sphere->setSelected(isSelected);
    }

    void Fixation::fixeInTheAir(const btVector3 &position)
    {
        this->rigidBody->getWorldTransform().setOrigin(position);

        // fixe root in the air
        btTransform local; local.setIdentity();
        btGeneric6DofConstraint *ct = new btGeneric6DofConstraint(*this->rigidBody,local,true);
        ct->setAngularLowerLimit(btVector3(0,0,0));
        ct->setAngularUpperLimit(btVector3(0,0,0));
        airFixation = ct;

        if(bulletEngine)
            bulletEngine->getBulletDynamicsWorld()->addConstraint(ct);
        else
            qDebug() << "set before (bulletEngine is null)";
    }

    void Fixation::unfixInTheAir()
    {
        if(bulletEngine != 0 && airFixation != 0)
        {
            bulletEngine->getBulletDynamicsWorld()->removeConstraint(airFixation);
            delete airFixation;
        }
    }

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
        localBone.setOrigin(btVector3(btScalar(0.), btScalar(-bone->getLength()*0.5 -radius), btScalar(0.)));

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

    void Fixation::addSensor(Sensor * sensor)
    {
        sensors.append(sensor);

        if(entity)
            entity->addLinkToSensor(sensor);
    }

    FixationProperties *Fixation::getInspectorWidget()
    {
        if(inspectorWidget == 0)
            inspectorWidget = new FixationProperties();

        inspectorWidget->setFixation(this);

        return inspectorWidget;
    }

    FixationProperties *Fixation::getEmptyInspectorWidget()
    {
        if(inspectorWidget == 0)
            inspectorWidget = new FixationProperties();

        return inspectorWidget;
    }

    void Fixation::setEntity(Entity * entity)
    {
        this->entity = entity;

        foreach(Bone *bone, bones)
            bone->setEntity(entity);
    }

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
