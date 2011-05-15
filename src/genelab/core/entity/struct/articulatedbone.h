#ifndef BONE_H
#define BONE_H

#include <QObject>
#include "classes.h"

namespace GeneLabCore {
    class ArticulatedBone : public QObject
    {
        Q_OBJECT
    public:
        explicit ArticulatedBone(QObject *parent = 0);
        ArticulatedBone(float alpha_max, float beta_min, float beta_max, float r_min, float r_max, float length);
        ~ArticulatedBone();

        float getLength();

        float rotationCapacity();
        float hingeCapacity();

        float getAlpha();
        float getBetaMin();

        /**
          * Fixe aticulation between angle_min and angle_max
          */
        void contractInNormalPosition();

        Fixation* getFixation();

        void initOgreBullet(OgreManager* ogreManager, BulletManager *bulletManager);
        void setup();
        void attachToParentFixation(Fixation* parentFix);


        OgreBulletDynamics::RigidBody *getRigidBody();

        QString toString();

    signals:

    public slots:

    private:

        // Articulation properties
        float alpha_min, alpha_max;
        float beta_min, beta_max;
        float r_min, r_max;

        // Bone properties
        float boneRadius;
        float boneLength;
        float boneMass;
        OgreBulletDynamics::RigidBody *rigidBody;

        // End Fixation (totally limited on each axis)
        Fixation* end;

        // Six dof constraint
        OgreBulletDynamics::SixDofConstraint *parentSixDofConstraint;

        // Ogre and Bullet
        OgreManager* ogreManager;
        BulletManager *bulletManager;
    };
}
#endif // BONE_H
