#ifndef BTBIOME_H
#define BTBIOME_H

#include <QObject>
#include <QVariant>

#include "mainfactory.h"

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

namespace GeneLabCore {

class btBiome : public QObject
{
    Q_OBJECT
public:
    explicit btBiome(MainFactory* factory, QVariant biomeData, QObject *parent = 0);

    virtual void setup();

    virtual void setBulletWorld(btDynamicsWorld* world) {
        this->world = world;
    }

signals:

public slots:

protected:
    QVariantMap data;
    btDynamicsWorld* world;
    MainFactory* factory;

};

}

#endif // BTBIOME_H
