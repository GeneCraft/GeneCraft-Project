#include "fixation.h"

// Qt
#include <QStringBuilder>
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
#include "widgets/entities/fixationpropertiescontroller.h"

#include "tools.h"
#include "effectors/effector.h"


namespace GeneCraftCore {

    const btScalar Fixation::PERCENT_BONE_INSIDE_FIX = 0.15f;

    #define FIXATION_DENSITY btBone::DENSITY/10
    #define FIXATION_FRICTION 0.7f

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

        this->rigidBody->setFriction(FIXATION_FRICTION);
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

        sphere = shapesFactory->createSphere(radius, initTransform, FIXATION_DENSITY);
        this->rigidBody     = sphere->getRigidBody();
        this->rigidBody->setFriction(FIXATION_FRICTION);
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
        while(bones.size()) {
            delete bones.at(0);
            bones.removeFirst();
        }

        while(sensors.size()) {
            entity->removeLinksToSensor(sensors.at(0));
            delete sensors.at(0);
            sensors.removeFirst();
        }

        while(effectors.size()) {
            entity->removeLinksToEffector(effectors.at(0));
            delete effectors.at(0);
            effectors.removeFirst();
        }

        if(this->airFixation) {
            shapesFactory->getWorld()->getBulletWorld()->removeConstraint(airFixation);
            delete this->airFixation;
        }

        if(!delegatedSetup && this->origin != 0)
            delete this->origin;

        if(!delegatedSetup)
            delete sphere;
    }

    void Fixation::remove() {

        foreach(Bone* b, bones) {
            b->remove();
        }

        while(sensors.size() > 0) {
            this->removeSensor(sensors.first());
        }

        while(effectors.size() > 0) {
            this->removeEffector(effectors.first());
        }
    }


    void Fixation::removeAndAttachChildrenTo(Fixation *parent) {

        foreach(Bone* b, bones) {

            btVector3 lo , up;
            b->getParentConstraint()->getAngularLowerLimit(lo);
            b->getParentConstraint()->getAngularUpperLimit(up);

            parent->addBone(b,b->getYAxis(),b->getZAxis(),lo,up);
        }
        bones.clear();

        while(sensors.size() > 0) {
            this->removeSensor(sensors.first());
        }

        while(effectors.size() > 0) {
            this->removeEffector(effectors.first());
        }
    }

    // ----------
    // -- BONE --
    // ----------

    void Fixation::addBone(Bone *bone, btScalar yAxis, btScalar zAxis, btVector3 &lowerLimits, btVector3 &upperLimits) {

        btQuaternion local1;
        local1.setRotation(btVector3(0, 1, 0), yAxis);
        btQuaternion local2;
        local2.setRotation(btVector3(0, 0, 1), zAxis);
        local1 *= local2;

        btQuaternion localOrientation = local1;

        btTransform localBone;
        localBone.setIdentity();
        localBone.setOrigin(btVector3(btScalar(0.), btScalar(-bone->getLength()*0.5 - radius), btScalar(0.)));

        btTransform localFix;
        localFix.setIdentity();
        localFix.setRotation(localOrientation);
        localFix.setOrigin(localFixation.getOrigin());

        btGeneric6DofConstraint * ct = new btGeneric6DofConstraint(*this->rigidBody,*bone->getRigidBody(),
                                                               localFix, localBone, false);

        ct->setBreakingImpulseThreshold(1./this->rigidBody->getInvMass() * 100);
        ct->setAngularLowerLimit(lowerLimits);
        ct->setAngularUpperLimit(upperLimits);

        // delete old parent constraint and set new
        if(bone->getParentConstraint() != NULL) {
            shapesFactory->getWorld()->getBulletWorld()->removeConstraint(bone->getParentConstraint());
            delete bone->getParentConstraint();
        }
        bone->setParentConstraint(ct);
        shapesFactory->getWorld()->getBulletWorld()->addConstraint(ct, true);

        bone->setParentFixation(this);
        bone->setEntity(entity);
        bones.append(bone);
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
        localBone.setOrigin(btVector3(btScalar(0.), btScalar(-bone->getLength()*0.5 - radius), btScalar(0.)));

        btTransform localFix;
        localFix.setIdentity();
        localFix.setRotation(localOrientation);
        localFix.setOrigin(localFixation.getOrigin());

        btGeneric6DofConstraint * ct = new btGeneric6DofConstraint(*this->rigidBody,*bone->getRigidBody(),
                                                               localFix, localBone, false);

        ct->setBreakingImpulseThreshold(1./this->rigidBody->getInvMass() * 100);
        ct->setAngularLowerLimit(lowerLimits);
        ct->setAngularUpperLimit(upperLimits);
        bone->setParentConstraint(ct);
        bone->setParentFixation(this);
        bone->setEntity(entity);
        bones.append(bone);

        return bone;
    }

    void Fixation::removeBone(Bone *bone) {
        this->bones.removeAll(bone);
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
    // -- EFFECTORS --
    // ---------------

    void Fixation::addEffector(Effector * effector)
    {
        effectors.append(effector);

        if(entity)
            entity->addLinkToEffector(effector);
    }

    void Fixation::removeEffector(Effector *effector){

        effectors.removeOne(effector);

        if(entity)
            entity->removeLinksToEffector(effector);
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
        if(!delegatedSetup)
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
        QVariantList effectorsVariantList;

        fixation.insert("radius",QVariant((double)radius));

        foreach(Bone *bone, bones) {
            bonesVariantList.append(bone->serialize());
        }

        foreach(Sensor *sensor, sensors) {
            sensorsVariantList.append(sensor->serialize());
        }

        foreach(Effector *effector, effectors) {
            effectorsVariantList.append(effector->serialize());
        }

        fixation.insert("bones", bonesVariantList);
        fixation.insert("sensors", sensorsVariantList);
        fixation.insert("effectors", effectorsVariantList);

        return fixation;
    }

    QVariant Fixation::generateEmpty()
    {
        QVariantMap fixation;

        // TODO right values ???
        fixation.insert("radius",(double) Tools::random(0.1,0.5));
        fixation.insert("bones", QVariantList());
        fixation.insert("sensors", QVariantList());
        fixation.insert("effectors", QVariantList());

        return fixation;
    }

    // -----------
    // -- TOOLS --
    // -----------

    void Fixation::setOutputsFrom(MotorFrom action) {
        QList<Bone *> bones = this->getBones();
        for(int i=0;i<bones.size();++i)
        {
            Bone *bone = bones.at(i);

            switch(action)
            {
                case fromDisabled:
                    bone->disableMotors();
                break;
                case fromBrain:
                    bone->setBrainMotors();
                break;
                case fromRandom:
                    bone->setRandomMotors();
                break;
                case fromNormal:
                    bone->setNormalPositionMotors();
                break;
            }

            bone->getEndFixation()->setOutputsFrom(action);
        }
    }

    bool Fixation::isInOnePiece() {
        foreach(Bone* b, bones) {
            if(!(b->getParentConstraint()->isEnabled()))
                return false;

            if(!b->getEndFixation()->isInOnePiece())
                return false;
        }

        return true;
    }
}
