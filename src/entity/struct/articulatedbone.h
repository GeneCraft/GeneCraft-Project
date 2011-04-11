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

        Fixation* getFixation();


        void initOgreBullet(GeneLabOgreBullet::OgreManager* ogreManager, GeneLabOgreBullet::BulletManager *bulletManager);
        void setup();
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

        GeneLabOgreBullet::OgreManager* ogreManager;
        GeneLabOgreBullet::BulletManager *bulletManager;
    };
}
#endif // BONE_H
