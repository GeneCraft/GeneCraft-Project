#ifndef BTWORLD_H
#define BTWORLD_H

#include <QObject>

#include "genelabcoreclasses.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "LinearMath/btTransform.h"

#include <deque>

namespace GeneLabCore {

    class btWorld : public QObject
    {
        Q_OBJECT
    public:
        explicit btWorld(QObject *parent = 0);

        // To create a new creature
        btTransform getSpawnPosition();
        // To add a created creature to the world
        void addCreature(Entity* ent);

    signals:

    public slots:

    protected:
        // Static object (ground, etc..)
        btScene*  scene;
        // Static parameters (gravity, etc...)
        btBiome*  biome;

        // Bullet engine
        BulletEngine*     bEngine;
        // Entity engine
        EntitiesEngine*   entitiesEngine;

        // OgreBullet World
        OgreBulletDynamics::DynamicsWorld *mWorld;
        OgreBulletCollisions::DebugDrawer *debugDrawer;

        // for entity "counting"
        int mNumEntitiesInstanced;
        // WTF ?
        int mMoveSpeed;

        // Rigid body created... don't know the purpose right now...
        std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
        std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;

    };

}

#endif // BTWORLD_H
