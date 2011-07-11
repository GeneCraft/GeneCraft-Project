#ifndef BTWORLD_H
#define BTWORLD_H

#include <QObject>

#include "genelabcoreclasses.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "LinearMath/btTransform.h"

#include <deque>
#include <QVariant>

#include "world/btscene.h"
#include "world/btbiome.h"


namespace GeneLabCore {

    class btWorld : public QObject
    {

    public:
        explicit btWorld(btFactory* factory, btShapesFactory* shapesFactory, QVariant worldData, QObject *parent = 0);

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

        // Data
        QVariantMap data;
    };

}

#endif // BTWORLD_H
