#ifndef BTBIOME_H
#define BTBIOME_H

#include <QObject>
#include <QVariant>

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "btfactory.h"

namespace GeneLabCore {

class btBiome : public QObject
{
    Q_OBJECT
public:
    explicit btBiome(btWorld* world, QVariant biomeData, QObject *parent = 0);

    virtual void setup();

    virtual void setBulletWorld(btDynamicsWorld* world) {
        this->world = world;
    }

signals:

public slots:

protected:
    QVariantMap data;
    btDynamicsWorld* world;
};

}

#endif // BTBIOME_H
