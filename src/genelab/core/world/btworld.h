#ifndef BTWORLD_H
#define BTWORLD_H

#include <QObject>

#include "genelabcoreclasses.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "LinearMath/btTransform.h"

#include <deque>
#include <QVariant>

#include "world/btscene.h"
#include "world/btbiome.h"


namespace GeneLabCore {

    class btWorld : public QObject
    {
        Q_OBJECT
    public:
        explicit btWorld(MainFactory* factory, QVariant worldData, QObject *parent = 0);

        // To create a new creature
        virtual btVector3 getSpawnPosition();

        // To add a created creature to the world
        virtual void addCreature(Entity* ent);

        void setScene(btScene* scene);
        void setBiome(btBiome* biome);

        btScene* getScene() { return scene; }
        btBiome* getBiome() { return biome; }

        btDynamicsWorld* getBulletWorld() { return world; }

        // To setup the world
        virtual void setup();

    signals:

    public slots:

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
        MainFactory* factory;

        // Bullet world
        btDynamicsWorld* world;

        // Data
        QVariantMap data;
    };

}

#endif // BTWORLD_H
