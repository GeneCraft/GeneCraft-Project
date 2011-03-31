#ifndef BULLETSCENE_H
#define BULLETSCENE_H

#include "classes.h"
#include "physics/physicsscene.h"

namespace GeneLabOgreBullet {
    class BulletScene : public GeneLabCore::PhysicsScene
    {
        Q_OBJECT
    public:
        explicit BulletScene(QObject *parent = 0);

    signals:

    public slots:

    };
}

#endif // BULLETSCENE_H
