#ifndef FIXATION_H
#define FIXATION_H

#include <QObject>
#include <QList>
#include "genelabcoreclasses.h"

namespace GeneLabCore {
    class Fixation : public QObject
    {
        Q_OBJECT
    public:
        explicit Fixation(QObject *parent = 0);
        ~Fixation();



        ArticulatedBone* addBone(float alpha,
                     float beta,
                     float length);

        ArticulatedBone* addBone(float alpha,
                     float beta_min, float beta_max,
                     float length);

        ArticulatedBone* addBone(float alpha,
                     float beta,
                     float r_min, float r_max,
                     float length);

        ArticulatedBone* addBone(float alpha,
                     float beta_min, float beta_max,
                     float r_min, float r_max,
                     float length);

        // OgreBullet
        /** create entity in Ogre and Bullet and attach all bones */
        void initOgreBullet(OgreManager* ogreManager, BulletManager *bulletManager);
        void setup(Ogre::Vector3 position);
        OgreBulletDynamics::RigidBody *getRigidBody();


        QList<ArticulatedBone*> getArticulatedBones();
        QString toString();

        float getRadius();

    signals:

    public slots:

    private:
        QList<ArticulatedBone*> articulatedBones;
        OgreBulletDynamics::RigidBody *rigidBody;

        OgreManager* ogreManager;
        BulletManager *bulletManager;

        float radius;
    };
}
#endif // FIXATION_H
