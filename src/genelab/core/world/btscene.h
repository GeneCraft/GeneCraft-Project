#ifndef BTSCENE_H
#define BTSCENE_H

#include <QObject>
#include <QVariant>

#include "mainfactory.h"
#include "spawn.h"
#include "genelabcoreclasses.h"

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {

class btScene : public QObject
{
    Q_OBJECT
public:
    explicit btScene(MainFactory* factory, QVariant sceneData, QObject *parent = 0);

    virtual void setup();

    btVector3 getSpawnPosition();

    virtual void setBulletWorld(btDynamicsWorld* world) {
        this->world = world;
    }

signals:

public slots:

protected:
    QVariantMap data;
    btDynamicsWorld* world;
    MainFactory* factory;
    QList<Spawn*> spawns;

};

}

#endif // BTSCENE_H
