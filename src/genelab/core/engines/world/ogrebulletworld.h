#ifndef OGREBULLETWORLD_H
#define OGREBULLETWORLD_H

#include "genelabcoreclasses.h"
#include "world.h"

#include <deque>

namespace GeneLabCore {

    class OgreBulletWorld : public World
    {
        Q_OBJECT
    public:
        OgreBulletWorld(BulletOgreEngine *btoEngine, QObject *parent = 0);

    signals:

    public slots:
        virtual void setup();
    private:

        BulletOgreEngine *btoEngine;

        // OgreBullet World
        OgreBulletDynamics::DynamicsWorld *mWorld;
        OgreBulletCollisions::DebugDrawer *debugDrawer;

        int mNumEntitiesInstanced;
        int mMoveSpeed;

        std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
        std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;

    };

}

#endif // OGREBULLETWORLD_H
