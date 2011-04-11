#include "ogrebulletentity.h"
#include "struct/articulation.h"
#include "sandboxtools.h"
#include "struct/treeshape.h"
#include "struct/fixation.h"
#include "struct/articulatedbone.h"
#include "struct/types.h"
#include <QList>
#include <QStack>
#include "graphic/ogremanager.h"
#include "physics/bulletmanager.h"
#include "Dynamics/Constraints/OgreBulletDynamics6DofConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "Dynamics/OgreBulletDynamicsRigidBody.h"
#include "Dynamics/Constraints/OgreBulletDynamicsPoint2pointConstraint.h"

namespace GeneLabOgreBullet {
    OgreBulletEntity::OgreBulletEntity(QString name, QString f, int gen, QObject *parent) :
        GeneLabCore::Entity(name, f, gen)
    {}

    void OgreBulletEntity::initOgreBullet(OgreManager* ogreManager, BulletManager* bulletManager)
    {
        this->ogreManager = ogreManager;
        this->bulletManager = bulletManager;

        // TODO add ogreManager and bulletManager to all fixation...
    }

    void OgreBulletEntity::setup()
    {
        // need call initOgreBullet before!
        if(ogreManager == NULL)
        {
            qDebug("ogreManager not initialized, please call initOgreBullet before."); // throw ...
            return;
        }

        if(bulletManager == NULL)
        {
            qDebug("bulletManager not initialized, please call initOgreBullet before."); // throw ...
            return;
        }

        // --
        // -- Setup the shape
        // --
        GeneLabOgreBullet::TreeShape *shape = this->getShape();
        shape->getRoot()->initOgreBullet(ogreManager,bulletManager);
        shape->getRoot()->setup();

        // attach the nose in the air
        //btGeneric6DofConstraint *ctRoot = new btGeneric6DofConstraint(*shape->getRoot()->getRigidBody()->getBulletRigidBody(),btTransform(btQuaternion(),btVector3(0,0,0)),true);
        btPoint2PointConstraint *ctRoot = new btPoint2PointConstraint(*shape->getRoot()->getRigidBody()->getBulletRigidBody(),btVector3(0,0,0));
        bulletManager->getWorld()->getBulletDynamicsWorld()->addConstraint(ctRoot);

        // setup recurcively the tree shape
        setupFixation(shape->getRoot());
    }

    void OgreBulletEntity::setupFixation(GeneLabOgreBullet::Fixation *fix)
    {
        // For each bones...
        QList<GeneLabOgreBullet::ArticulatedBone*> articulatedBones = fix->getArticulatedBones();
        GeneLabOgreBullet::ArticulatedBone *aBone;
        for(int i=0;i<articulatedBones.length();i++)
        {
            // --
            // -- setup the bone
            // --
            aBone = articulatedBones.at(i);
            aBone->initOgreBullet(ogreManager,bulletManager);
            aBone->setup();

            // attach the bone to the parent fixation
            OgreBulletDynamics::SixDofConstraint *ctParentFixToBone = new OgreBulletDynamics::SixDofConstraint(
                    fix->getRigidBody(),aBone->getRigidBody(),Ogre::Vector3(0,0,0),Ogre::Quaternion(),Ogre::Vector3(0,aBone->getLength(),0),Ogre::Quaternion());
            bulletManager->getWorld()->addConstraint(ctParentFixToBone);

            // configure the attachement
            btGeneric6DofConstraint *ctParentFixToBone_b = (btGeneric6DofConstraint*) ctParentFixToBone->getBulletTypedConstraint();

            // OgreBulletDynamics::SixDofConstraint::setAngularLowerLimit isn't correct ! We use directly Bullet methods
            static_cast<btGeneric6DofConstraint* > (ctParentFixToBone->getBulletTypedConstraint())->setAngularLowerLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(1,-1.5,1)));
            static_cast<btGeneric6DofConstraint* > (ctParentFixToBone->getBulletTypedConstraint())->setAngularUpperLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,1.5,0)));

            for(int i=0;i<1;i++)
            {
                if (i == 1)
                    continue;

                btRotationalLimitMotor *motor = ctParentFixToBone_b->getRotationalLimitMotor(i);
                motor->m_enableMotor = true;
                motor->m_targetVelocity = 4;
                motor->m_maxMotorForce = 100;
            }

            // --
            // -- setup the fixation of the bone
            // --
            GeneLabOgreBullet::Fixation *sonFix = aBone->getFixation();
            sonFix->initOgreBullet(ogreManager,bulletManager);
            sonFix->setup();

            // attach articulatedBone to its fixation
            OgreBulletDynamics::SixDofConstraint *ctBoneToSonFix = new OgreBulletDynamics::SixDofConstraint(
                    sonFix->getRigidBody(),aBone->getRigidBody(),Ogre::Vector3(0,0,0),Ogre::Quaternion(),Ogre::Vector3(0, -aBone->getLength(),0),Ogre::Quaternion());

            // constraint articulation
            static_cast<btGeneric6DofConstraint* > (ctBoneToSonFix->getBulletTypedConstraint())->setAngularLowerLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,0,0)));
            static_cast<btGeneric6DofConstraint* > (ctBoneToSonFix->getBulletTypedConstraint())->setAngularUpperLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,0,0)));

            bulletManager->getWorld()->addConstraint(ctBoneToSonFix);



            // setup recurcively
            setupFixation(sonFix);
        }
    }

    void OgreBulletEntity::setShape(TreeShape *shape) {
        this->shape = shape;
    }

    TreeShape* OgreBulletEntity::getShape() {
        return this->shape;
    }
}
