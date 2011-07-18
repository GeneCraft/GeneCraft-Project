#include "btworld.h"

#include "btbiome.h"
#include "btscene.h"

#include "bullet/bulletengine.h"
#include "entities/entitiesengine.h"

#include "btfactory.h"
#include "btshapesfactory.h"

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btContinuousDynamicsWorld.h"
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"

#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include <btBulletDynamicsCommon.h>

#include <QDebug>
namespace GeneLabCore {

    btWorld::btWorld(btFactory* factory, btShapesFactory* shapesFactory, QVariant worldData, QObject *parent) :
        QObject(parent)
    {
        this->data = worldData.toMap();
        this->factory = factory;
        this->shapesFactory = shapesFactory;
        this->btEngine = static_cast<BulletEngine*>(factory->getEngines().find("Bullet").value());
        entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());

    }

    // To create a new creature
    btVector3 btWorld::getSpawnPosition() {
        return scene->getSpawnPosition();
    }

    // To add a created creature to the world
    void btWorld::addCreature(Entity*) {

    }

    // Setup of the world
    void btWorld::setup() {

        // create new bullet world
        btBroadphaseInterface* broadphase = new btDbvtBroadphase();
        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
        world = new btDiscreteDynamicsWorld(dispatcher, broadphase,solver,collisionConfiguration);


        /*
        btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);

        btCollisionShape* fallShape = new btSphereShape(1);


        btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
        btRigidBody::btRigidBodyConstructionInfo
                groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
        btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
        world->addRigidBody(groundRigidBody);


        btDefaultMotionState* fallMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
        btScalar mass = 1;
        btVector3 fallInertia(0,0,0);
        fallShape->calculateLocalInertia(mass,fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
        btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
        world->addRigidBody(fallRigidBody);


        for (int i=0 ; i<300 ; i++) {
                world->stepSimulation(1/60.f,10);

                btTransform trans;
                fallRigidBody->getMotionState()->getWorldTransform(trans);

                qDebug() << "sphere height: "<< trans.getOrigin().getX() << trans.getOrigin().getY();
        }
        */

        // Set the world to the subworld classes
        this->biome->setBulletWorld(world);
        this->scene->setBulletWorld(world);

        // Setup the biome+scene
        this->biome->setup();
        this->scene->setup();

        // Add the world to the bullet engine
        btEngine->addWorld(world);
    }

    // To set the scene
    void btWorld::setScene(btScene* scene) {
        this->scene = scene;
        this->scene->setBulletWorld(world);
    }

    // To set the biome
    void btWorld::setBiome(btBiome* biome) {
        this->biome = biome;
        this->biome->setBulletWorld(world);
    }


}
