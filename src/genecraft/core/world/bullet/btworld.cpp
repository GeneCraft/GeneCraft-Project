/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "btworld.h"

#include "btbiome.h"
#include "btscene.h"

#include "bullet/bulletengine.h"
#include "entities/entitiesengine.h"

#include "btfactory.h"
#include "btshapesfactory.h"

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletCollision/BroadphaseCollision/btOverlappingPairCache.h"

#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include <btBulletDynamicsCommon.h>

#include <QDebug>
namespace GeneCraftCore {


    btWorld::btWorld(btFactory* factory, btShapesFactory* shapesFactory, QObject *parent) :
        QObject(parent)
    {
        // TODO
        this->data = QVariantMap();
        this->factory = factory;
        this->shapesFactory = shapesFactory;
        this->btEngine = static_cast<BulletEngine*>(factory->getEngineByName("Bullet"));
        entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngineByName("Entities"));

    }

    btWorld::btWorld(btFactory* factory, btShapesFactory* shapesFactory, QVariant worldData, QObject *parent) :
        QObject(parent)
    {
        this->data = worldData.toMap();
        this->factory = factory;
        this->shapesFactory = shapesFactory;
        this->btEngine = static_cast<BulletEngine*>(factory->getEngineByName("Bullet"));
        entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngineByName("Entities"));

    }

    btWorld::~btWorld() {

        this->shapesFactory->setWorld(NULL);

        delete this->scene;
        delete this->biome;

        this->cleanBulletWorld();
    }

    void btWorld::cleanBulletWorld() {

        // from : http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=638&view=next
        //cleanup in the reverse order of creation/initialization

        //remove the rigidbodies from the dynamics world and delete them
        int i;
        for (i=world->getNumCollisionObjects()-1; i>=0 ;i--)
        {
            btCollisionObject* obj = world->getCollisionObjectArray()[i];
            world->removeCollisionObject( obj );
            delete obj;
        }

        btEngine->removeWorld(world);

        delete world;
        delete solver;
        delete dispatcher;
        delete collisionConfiguration;
        delete broadphase;
        delete ovPairCache;

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
        ovPairCache             = new btSortedOverlappingPairCache;
        broadphase              = new btDbvtBroadphase(ovPairCache);
        collisionConfiguration  = new btDefaultCollisionConfiguration();
        dispatcher              = new btCollisionDispatcher(collisionConfiguration);
        solver                  = new btSequentialImpulseConstraintSolver();
        world                   = new btDiscreteDynamicsWorld(dispatcher, broadphase,solver,collisionConfiguration);

        btContactSolverInfo& info = world->getSolverInfo();
        info.m_numIterations = 20; // 20

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
