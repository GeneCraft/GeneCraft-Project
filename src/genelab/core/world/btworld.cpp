#include "btworld.h"

#include "btbiome.h"
#include "btscene.h"

#include "bullet/bulletengine.h"
#include "entities/entitiesengine.h"

#include "mainfactory.h"

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"



// Shapes
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "bulletogre/shapes/btosphere.h"
#include "bulletogre/shapes/btobox.h"
#include "bulletogre/shapes/btocylinder.h"
#include "btoshapesfactory.h"


namespace GeneLabCore {

    btWorld::btWorld(MainFactory* factory, QObject *parent) :
        QObject(parent)
    {
        this->factory = factory;
        this->btEngine = static_cast<BulletEngine*>(factory->getEngines().find("Bullet").value());
        entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());


    }

    // To create a new creature
    btTransform btWorld::getSpawnPosition() {
        btTransform pos;
        pos.setIdentity();
        return pos;
    }

    // To add a created creature to the world
    void btWorld::addCreature(Entity* ent) {

    }

    // Setup of the world
    void btWorld::setup() {

        // create new bullet world
        btBroadphaseInterface* broadphase = new btDbvtBroadphase();
        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
        world = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

        // Setup the biome+scene
        //this->biome->setup(world);
        //this->scene->setup(world);

        // TO BIOME
        world->setGravity(btVector3(0,-9.81,0));

        btStaticPlaneShape *collisionShape = new btStaticPlaneShape(btVector3(0,1,0),0);
        btTransform worldTransform;
        worldTransform.setIdentity();
        btDefaultMotionState* groundMotionState = new btDefaultMotionState(worldTransform);
        btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,collisionShape,btVector3(0,0,0));

        btRigidBody *rigidBody = new btRigidBody(groundRigidBodyCI);
        rigidBody->setActivationState(DISABLE_DEACTIVATION);
        world->addRigidBody(rigidBody);

        // Add the world to the bullet engine
        btEngine->addWorld(world);
    }



}
