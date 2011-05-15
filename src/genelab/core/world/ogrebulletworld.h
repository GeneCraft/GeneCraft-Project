#ifndef OGREBULLETWORLD_H
#define OGREBULLETWORLD_H

#include "classes.h"
#include "core/world/world.h"

#include <deque>

namespace GeneLabCore {

    class OgreBulletWorld : public World
    {
        Q_OBJECT
    public:
        explicit OgreBulletWorld(OgreManager* ogreManager, BulletManager* bulletManager,
                                 QObject *parent = 0);

    signals:

    public slots:
        virtual void setup();
    private:
        OgreManager* ogreManager;
        BulletManager* bulletManager;


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
