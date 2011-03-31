#ifndef OGREBULLETMANAGER_H
#define OGREBULLETMANAGER_H

#include <QObject>
#include <deque>
#include "classes.h"
#include "physics/physicsengine.h"

namespace GeneLabOgreBullet {
    class BulletManager : public GeneLabCore::PhysicsEngine
    {
        Q_OBJECT
    public:
        explicit BulletManager(QObject *parent = 0);
        void init(OgreManager* ogreRoot);
        GeneLabCore::PhysicsScene* getPhysicsScene();

    signals:

    public slots:
        void physicsStep();

    protected:
        OgreManager* ogre;
        Ogre::Root* mOgreRoot;
        Ogre::SceneManager* mSceneMgr;

        OgreBulletDynamics::DynamicsWorld *mWorld;   // OgreBullet World
        OgreBulletCollisions::DebugDrawer *debugDrawer;
        int mNumEntitiesInstanced;
        int mMoveSpeed;
        std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
        std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;


    };
}
#endif // OGREBULLETMANAGER_H
