#ifndef BTSCENE_H
#define BTSCENE_H

#include <QObject>
#include <QVariant>

#include "spawn.h"
#include "genelabcoreclasses.h"

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {

class btScene : public QObject
{
    Q_OBJECT
public:
    explicit btScene(btWorld* world, QVariant sceneData, QObject *parent = 0);

    virtual void setup();

    btVector3 getSpawnPosition();

    virtual void setBulletWorld(btDynamicsWorld* bulletWorld) {
        this->bulletWorld = bulletWorld;
    }

signals:

public slots:

protected:
    QVariantMap data;
    btDynamicsWorld* bulletWorld;
    btWorld* world;
    QList<Spawn*> spawns;

};

}

#endif // BTSCENE_H
