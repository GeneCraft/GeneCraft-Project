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

namespace GeneLabCore {

    btWorld::btWorld(MainFactory* factory, QVariant worldData, QObject *parent) :
        QObject(parent)
    {
        this->data = worldData.toMap();
        this->factory = factory;
        this->btEngine = static_cast<BulletEngine*>(factory->getEngines().find("Bullet").value());
        entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());

    }

    // To create a new creature
    btVector3 btWorld::getSpawnPosition() {
        return scene->getSpawnPosition();
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
