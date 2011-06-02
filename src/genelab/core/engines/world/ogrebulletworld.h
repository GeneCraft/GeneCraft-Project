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
        OgreBulletWorld(MainFactory *mainFactory, QObject *parent = 0);

    signals:

    public slots:
        virtual void setup();
    private:

        MainFactory *mainFactory;
        BulletOgreEngine *btoEngine;
        EntitiesEngine* entitiesEngine;

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
