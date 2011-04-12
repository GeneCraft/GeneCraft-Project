#ifndef BONE_H
#define BONE_H

#include <QObject>
#include "classes.h"

namespace GeneLabOgreBullet {
    class ArticulatedBone : public QObject
    {
        Q_OBJECT
    public:
        explicit ArticulatedBone(QObject *parent = 0);
        ArticulatedBone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length);
        ~ArticulatedBone();

        float getLength();

        float rotationCapacity();
        float hingeCapacity();

        float getAlpha();
        float getBeta();

        /**
          * Fixe aticulation between angle_min and angle_max
          */
        void contractInNormalPosition();

        Fixation* getFixation();

        void initOgreBullet(GeneLabOgreBullet::OgreManager* ogreManager, GeneLabOgreBullet::BulletManager *bulletManager);
        void setup();
        void attachToParentFixation(Fixation* parentFix);


        OgreBulletDynamics::RigidBody *getRigidBody();

        QString toString();

    signals:

    public slots:

    private:
        float alpha, beta_min, beta_max;
        float r_min, r_max;
        float length;
        Fixation* end;

        // Six dof constraint
        OgreBulletDynamics::RigidBody *rigidBody;
        OgreBulletDynamics::SixDofConstraint *parentSixDofConstraint;


        GeneLabOgreBullet::OgreManager* ogreManager;
        GeneLabOgreBullet::BulletManager *bulletManager;
    };
}
#endif // BONE_H
