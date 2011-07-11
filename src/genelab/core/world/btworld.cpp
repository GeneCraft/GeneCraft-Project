#include "btworld.h"

#include "btbiome.h"
#include "btscene.h"

#include "bullet/bulletengine.h"
#include "entities/entitiesengine.h"

#include "btfactory.h"
#include "btshapesfactory.h"

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"

#include <QDebug>

/*
#include "BulletMultiThreaded/btParallelConstraintSolver.h"
#include "BulletMultiThreaded/btThreadSupportInterface.h"
#include "BulletMultiThreaded/SequentialThreadSupport.h"
#include "BulletMultiThreaded/PosixThreadSupport.h"
#include "BulletCollision/CollisionDispatch/btSimulationIslandManager.h"
 */

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

//        SequentialThreadSupport::SequentialThreadConstructionInfo tci("solverThreads",SolverThreadFunc,SolverlsMemoryFunc);
//        SequentialThreadSupport* threadSupport = new SequentialThreadSupport(tci);
//        threadSupport->startSPU();


//	PosixThreadSupport::ThreadConstructionInfo solverConstructionInfo("solver", SolverThreadFunc, SolverlsMemoryFunc, 6);
	
//	PosixThreadSupport* threadSupport = new PosixThreadSupport(solverConstructionInfo);

//        btSequentialImpulseConstraintSolver* solver = new btParallelConstraintSolver(threadSupport);
        //this solver requires the contacts to be in a contiguous pool, so avoid dynamic allocation
//        dispatcher->setDispatcherFlags(btCollisionDispatcher::CD_DISABLE_CONTACTPOOL_DYNAMIC_ALLOCATION);


        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
        world = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

//        world->getSimulationIslandManager()->setSplitIslands(false);
//        world->getSolverInfo().m_numIterations = 10; // A varier pour des contraintes plus fermes
//        world->getSolverInfo().m_solverMode = SOLVER_SIMD+SOLVER_USE_WARMSTARTING;//+SOLVER_RANDMIZE_ORDER;

//        world->getDispatchInfo().m_enableSPU = true;

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
