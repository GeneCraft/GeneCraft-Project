#ifndef BTSCENE_H
#define BTSCENE_H

#include <QObject>
#include <QVariant>

#include "spawn.h"
#include "genecraftcoreclasses.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "LinearMath/btVector3.h"
#include "bullet/shapes/btshape.h"

namespace GeneCraftCore {

class btScene : public QObject
{

public:
    explicit btScene(btWorld* world, QVariant sceneData, QObject *parent = 0);
    ~btScene();

    virtual void setup();

    btVector3 getSpawnPosition();

    virtual void setBulletWorld(btDynamicsWorld* bulletWorld) {
        this->bulletWorld = bulletWorld;
    }

protected:
    QVariantMap data;
    btDynamicsWorld* bulletWorld;
    btWorld* world;
    QList<Spawn*> spawns;
    btDefaultMotionState* groundMotionState;
    btStaticPlaneShape *collisionShape;
    btRigidBody *rigidBody;
    QList<btShape*> shapes;

};

}

#endif // BTSCENE_H
