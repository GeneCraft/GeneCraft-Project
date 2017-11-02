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

#ifndef BTWORLD_H
#define BTWORLD_H

#include <QObject>

#include "genecraftcoreclasses.h"
#include <btBulletDynamicsCommon.h>

#include <deque>
#include <QJsonObject>

#include "bullet/btscene.h"
#include "bullet/btbiome.h"


namespace GeneCraftCore {

    class btWorld : public QObject
    {

    public:

        // To create a default world
        btWorld(btFactory* factory, btShapesFactory* shapesFactory, QObject *parent = 0);

        // To create a world from serialization data
        btWorld(btFactory* factory, btShapesFactory* shapesFactory, QJsonObject worldData, QObject *parent = 0);
        ~btWorld();

        // To create a new creature
        virtual btVector3 getSpawnPosition();

        // To add a created creature to the world
        virtual void addCreature(Entity* ent);

        void setScene(btScene* scene);
        void setBiome(btBiome* biome);

        btScene* getScene() { return scene; }
        btBiome* getBiome() { return biome; }

        btDynamicsWorld* getBulletWorld() { return this->world; }

        btFactory *getFactory() {return factory; }
        btShapesFactory *getShapesFactory() {return shapesFactory; }

        // To setup the world
        virtual void setup();

    protected:

        // To clean the bullet world
        void cleanBulletWorld();

        // Static object (ground, etc..)
        btScene*  scene;

        // Static parameters (gravity, etc...)
        btBiome*  biome;

        // Bullet engine
        BulletEngine*   btEngine;

        // Entity engine
        EntitiesEngine* entitiesEngine;

        // Factory in case of
        btFactory* factory;
        btShapesFactory* shapesFactory;

        // Bullet world
        btDiscreteDynamicsWorld* world;
        btOverlappingPairCache* ovPairCache;
        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;

        // Data
        QJsonObject data;
    };

}

#endif // BTWORLD_H
