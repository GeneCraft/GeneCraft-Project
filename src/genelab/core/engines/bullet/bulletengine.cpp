#include "bulletengine.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "OGRE/Ogre.h"
#include "ogreengine.h"
#include <QDebug>

namespace GeneLabCore {
    using namespace Ogre;

    BulletEngine::BulletEngine(QObject *parent) :
        Engine(parent)
    {
        physicsEnable = false;
    }

//    OgreBulletDynamics::DynamicsWorld* BulletEngine::getDynamicsWorld() {
//        return mWorld;
//    }

    void BulletEngine::init(/*OgreEngine* ogreEngine*/) {

        //this->ogreEngine = ogreEngine;

        // create world
        btBroadphaseInterface* broadphase = new btDbvtBroadphase();

        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

        bulletDynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
        bulletDynamicsWorld->setGravity(btVector3(0,-9.81,0));

//        Ogre::Vector3 gravityVector(0,-9.81,0); // gravity vector for Bullet
//        Ogre::AxisAlignedBox bounds(Ogre::Vector3 (-1000, -1000, -1000), //aligned box for Bullet
//                                   Ogre::Vector3 (1000,  1000,  1000));

//        // start Bullet
//        mWorld = new OgreBulletDynamics::DynamicsWorld(ogreEngine->getOgreSceneManager(), bounds, gravityVector);

//        bulletDynamicsWorld = mWorld->getBulletDynamicsWorld();


//        // add Debug info display tool
//        debugDrawer = new OgreBulletCollisions::DebugDrawer();
//        debugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
//        mWorld->setDebugDrawer(debugDrawer);
//        mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers

//        Ogre::SceneNode *node = ogreEngine->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
//        node->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));

    }

    void BulletEngine::step() {
        if(physicsEnable)
            bulletDynamicsWorld->stepSimulation(1/60.0, 10);
    }
}
