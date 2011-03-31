#include "physics/bulletmanager.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "OGRE/Ogre.h"
#include "graphic/ogremanager.h"

#include <QDebug>

namespace GeneLabOgreBullet {
    using namespace Ogre;

    BulletManager::BulletManager(QObject *parent) :
        Engine(parent)
    {
    }

    BulletScene* BulletManager::getPhysicsScene() {
        return NULL;
    }

    void BulletManager::init(OgreManager* ogre) {
        Ogre::Vector3 gravityVector(0,-9.81,0); // gravity vector for Bullet
        Ogre::AxisAlignedBox bounds(Ogre::Vector3 (-10000, -10000, -10000), //aligned box for Bullet
                                   Ogre::Vector3 (10000,  10000,  10000));
        this->ogre = ogre;
        mOgreRoot = ogre->getRoot();
        mSceneMgr = ogre->getOgreScene();

        mMoveSpeed = 50;   // defined in ExampleFrameListener
        mNumEntitiesInstanced = 0; // how many shapes are created
        // Start Bullet
        mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, bounds, gravityVector);
        // add Debug info display tool
        debugDrawer = new OgreBulletCollisions::DebugDrawer();
        debugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
        mWorld->setDebugDrawer(debugDrawer);
        mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers

        Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
        node->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));

        // Define a floor plane mesh
        Entity *ent;
        Plane p;
        p.normal = Vector3(0,1,0); p.d = 0;
        MeshManager::getSingleton().createPlane("FloorPlane",
                                                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                p, 200000, 200000, 20, 20, true, 1, 9000, 9000,
                                                Vector3::UNIT_Z);
        // Create an entity (the floor)
        ent = mSceneMgr->createEntity("floor", "FloorPlane");
        ent->setMaterialName("Examples/BumpyMetal");
        mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

        // add collision detection to it
        OgreBulletCollisions::CollisionShape *Shape;
        Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0); // (normal vector, distance)
        // a body is needed for the shape
        OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody("BasePlane",
                                                                                            mWorld);
        defaultPlaneBody->setStaticShape(Shape, 0.1, 0.8);// (shape, restitution, friction)
        // push the created objects to the deques
        mShapes.push_back(Shape);
        mBodies.push_back(defaultPlaneBody);
    }
    int cpt = 99;

    void BulletManager::beforeStep() {
        cpt++;
        if(cpt%30 == 0) {
            qDebug() << "adding a box !";
            Vector3 size = Vector3::ZERO;	// size of the box
            // starting position of the box
            Camera* mCamera = ogre->getOgreScene()->getCamera("first");
            Vector3 position = (mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 10);

            // create an ordinary, Ogre mesh with texture
            Entity *entity = mSceneMgr->createEntity(
                            "Box" + StringConverter::toString(mNumEntitiesInstanced),
                            "cube.mesh");

            entity->setCastShadows(true);


            qDebug() << "entity created";

            // we need the bounding box of the box to be able to set the size of the Bullet-box
            AxisAlignedBox boundingB = entity->getBoundingBox();
            size = boundingB.getSize(); size /= 2.0f; // only the half needed
            size *= 0.95f;	// Bullet margin is a bit bigger so we need a smaller size
                                                            // (Bullet 2.76 Physics SDK Manual page 18)
            entity->setMaterialName("Examples/Rockwall");
            entity->setCastShadows(true);


            qDebug() << "material too";

            SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
            node->attachObject(entity);
            node->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us
            size *= 0.05f;						// don't forget to scale down the Bullet-box too


            qDebug() << "attached !";
            // after that create the Bullet shape with the calculated size
            OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);
            // and the Bullet rigid body
            OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
                            "defaultBoxRigid" + StringConverter::toString(mNumEntitiesInstanced),
                            mWorld);
            defaultBody->setShape(	node,
                                    sceneBoxShape,
                                    0.6f,			// dynamic body restitution
                                    0.6f,			// dynamic body friction
                                    1.0f, 			// dynamic bodymass
                                    position,		// starting position of the box
                                    Quaternion(0,0,0,1));// orientation of the box
            mNumEntitiesInstanced++;

            qDebug() << "shape ok";
            defaultBody->setLinearVelocity(
                                    mCamera->getDerivedDirection().normalisedCopy() * 7.0f ); // shooting speed


            qDebug() << "velocity too";
            // push the created objects to the dequese
            mShapes.push_back(sceneBoxShape);
            mBodies.push_back(defaultBody);

            qDebug() << "end";
        }
    }

    void BulletManager::afterStep() {

    }

    void BulletManager::step() {
        //qDebug() << "physic step";

        mWorld->stepSimulation(1000/30, 3);
    }
}
