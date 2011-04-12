#include "articulatedbone.h"
#include "entity/struct/fixation.h"
#include "sandboxtools.h"
#include "OgreBulletDynamicsConstraint.h"
#include "Dynamics/Constraints/OgreBulletDynamics6DofConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"

namespace GeneLabOgreBullet {
    ArticulatedBone::ArticulatedBone(QObject *parent) :
        QObject(parent)
    {
        end = new Fixation();
    }

    ArticulatedBone::~ArticulatedBone() {
        delete end;
    }

    ArticulatedBone::ArticulatedBone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length) {

        this->alpha = alpha;
        this->beta_min = beta_min;
        this->beta_max = beta_max;
        this->r_min = r_min;
        this->r_max = r_max;
        this->length = length;

        end = new Fixation();
    }

    float ArticulatedBone::getLength() {
        return this->length;
    }

    float ArticulatedBone::rotationCapacity() {
        return r_max - r_min;
    }

    float ArticulatedBone::hingeCapacity() {
        return beta_max - beta_min;
    }

    float ArticulatedBone::getAlpha() {
        return alpha;
    }

    float ArticulatedBone::getBeta() {
        return beta_min;
    }

    Fixation* ArticulatedBone::getFixation() {
        return end;
    }

    OgreBulletDynamics::RigidBody *ArticulatedBone::getRigidBody()
    {
        return this->rigidBody;
    }

    void ArticulatedBone::initOgreBullet(GeneLabOgreBullet::OgreManager* ogreManager, GeneLabOgreBullet::BulletManager *bulletManager)
    {
        this->ogreManager = ogreManager;
        this->bulletManager = bulletManager;
    }

    void ArticulatedBone::setup()
    {
        // create the bones
        this->rigidBody = SandboxTools::addBox(ogreManager,bulletManager,Ogre::Vector3(0,9,0),Ogre::Vector3(0.2,this->length,0.2));

        // attach fixation to bones
        end->initOgreBullet(ogreManager,bulletManager);
        end->setup();

        // attach articulatedBone to its fixation
        OgreBulletDynamics::SixDofConstraint *ctBoneToSonFix = new OgreBulletDynamics::SixDofConstraint(
                end->getRigidBody(),getRigidBody(),Ogre::Vector3(0,0,0),Ogre::Quaternion(),Ogre::Vector3(0, -getLength(),0),Ogre::Quaternion());

        // constraint articulation
        static_cast<btGeneric6DofConstraint* > (ctBoneToSonFix->getBulletTypedConstraint())->setAngularLowerLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,0,0)));
        static_cast<btGeneric6DofConstraint* > (ctBoneToSonFix->getBulletTypedConstraint())->setAngularUpperLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,0,0)));

        bulletManager->getWorld()->addConstraint(ctBoneToSonFix);
    }

    QString ArticulatedBone::toString() {
        return "-" + QString::number(length) + "-" + this->end->toString();
    }

    void ArticulatedBone::attachToParentFixation(Fixation* parentFix)
    {
        // attach the bone to the parent fixation
        parentSixDofConstraint = new OgreBulletDynamics::SixDofConstraint(parentFix->getRigidBody(),
                                                                          getRigidBody(),
                                                                          Ogre::Vector3(0,0,0),
                                                                          Ogre::Quaternion(),
                                                                          Ogre::Vector3(0,getLength(),0),
                                                                          Ogre::Quaternion());

        bulletManager->getWorld()->addConstraint(parentSixDofConstraint);

        // configure the attachement
        btGeneric6DofConstraint *ctParentFixToBone_b = (btGeneric6DofConstraint*) parentSixDofConstraint->getBulletTypedConstraint();

        // OgreBulletDynamics::SixDofConstraint::setAngularLowerLimit isn't correct ! We use directly Bullet methods
        ctParentFixToBone_b->setAngularLowerLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(1,-1.5,1)));
        ctParentFixToBone_b->setAngularUpperLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,1.5,0)));

        for(int i=0;i<1;i++)
        {
            if (i == 1)
                continue;

            btRotationalLimitMotor *motor = ctParentFixToBone_b->getRotationalLimitMotor(i);
            motor->m_enableMotor = true;
            motor->m_targetVelocity = 4;
            motor->m_maxMotorForce = 100;
        }
    }

    void ArticulatedBone::contractInNormalPosition()
    {
        // configure the attachement
        btGeneric6DofConstraint *ctParentFixToBone_b = (btGeneric6DofConstraint*) parentSixDofConstraint->getBulletTypedConstraint();

        //ctParentFixToBone_b->setAngularLowerLimit(btVector3(0,0,0));
        //ctParentFixToBone_b->setAngularUpperLimit(btVector3(0,0,0));

        //ctParentFixToBone_b->setAngularLowerLimit(btVector3(alpha,beta_max - beta_min,r_max - r_min));
        //ctParentFixToBone_b->setAngularUpperLimit(btVector3(alpha,beta_max - beta_min,r_max - r_min));

        for(int i=0;i<3;i++)
        {
            btRotationalLimitMotor *motor = ctParentFixToBone_b->getRotationalLimitMotor(i);

            motor->m_hiLimit = 0;
            motor->m_loLimit = 0;
            motor->m_maxLimitForce = 100000;
            motor->m_enableMotor = true;
            motor->m_targetVelocity = 0;
            motor->m_maxMotorForce = 1;
        }



    }
}
