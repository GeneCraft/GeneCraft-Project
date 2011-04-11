#ifndef FIXATION_H
#define FIXATION_H

#include <QObject>
#include <QList>
#include "classes.h"

namespace GeneLabOgreBullet {
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
        void initOgreBullet(GeneLabOgreBullet::OgreManager* ogreManager, GeneLabOgreBullet::BulletManager *bulletManager);
        void setup();
        OgreBulletDynamics::RigidBody *getRigidBody();


        QList<ArticulatedBone*> getArticulatedBones();
        QString toString();

    signals:

    public slots:

    private:
        QList<ArticulatedBone*> articulatedBones;
        OgreBulletDynamics::RigidBody *rigidBody;

        GeneLabOgreBullet::OgreManager* ogreManager;
        GeneLabOgreBullet::BulletManager *bulletManager;
    };
}
#endif // FIXATION_H
