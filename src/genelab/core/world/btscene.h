#ifndef BTSCENE_H
#define BTSCENE_H

#include <QObject>
#include <QVariant>

#include "mainfactory.h"

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

namespace GeneLabCore {

class btScene : public QObject
{
    Q_OBJECT
public:
    explicit btScene(MainFactory* factory, QVariant sceneData, QObject *parent = 0);

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

#endif // BTSCENE_H
