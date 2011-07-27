#ifndef BTWORLD_H
#define BTWORLD_H

#include <QObject>

#include "genecraftcoreclasses.h"


#include <btBulletDynamicsCommon.h>

#include <deque>
#include <QVariant>

#include "world/btscene.h"
#include "world/btbiome.h"


namespace GeneCraftCore {

    class btWorld : public QObject
    {

    public:

        // To create a default world
        btWorld(btFactory* factory, btShapesFactory* shapesFactory, QObject *parent = 0);

        // To create a world from serialization data
        btWorld(btFactory* factory, btShapesFactory* shapesFactory, QVariant worldData, QObject *parent = 0);
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
        QVariantMap data;
    };

}

#endif // BTWORLD_H
