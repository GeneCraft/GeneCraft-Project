#ifndef OGREBULLETMANAGER_H
#define OGREBULLETMANAGER_H

#include <QObject>
#include <deque>
#include "classes.h"
#include "engine/engine.h"

namespace GeneLabOgreBullet {
    class BulletManager : public GeneLabCore::Engine
    {
        Q_OBJECT
    public:
        explicit BulletManager(QObject *parent = 0);

        BulletScene* getPhysicsScene();

        OgreBulletDynamics::DynamicsWorld *getWorld();

    signals:

    public slots:
        void beforeStep();
        void step();
        void afterStep();
        void init(OgreManager* ogreRoot);

    protected:
        OgreManager*        ogre;
        Ogre::Root*         mOgreRoot;
        Ogre::SceneManager* mSceneMgr;

        // OgreBullet World
        OgreBulletDynamics::DynamicsWorld *mWorld;
        OgreBulletCollisions::DebugDrawer *debugDrawer;

        int mNumEntitiesInstanced;
        int mMoveSpeed;

        std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
        std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;


    };
}
#endif // OGREBULLETMANAGER_H
