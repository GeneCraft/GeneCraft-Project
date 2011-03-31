#ifndef OGREBULLETWORLD_H
#define OGREBULLETWORLD_H

#include "classes.h"
#include "world/world.h"

namespace GeneLabOgreBullet {

    class OgreBulletWorld : public GeneLabCore::World
    {
        Q_OBJECT
    public:
        explicit OgreBulletWorld(QObject *parent = 0);

        void setPhysics(GeneLabCore::PhysicsScene* scene);
        void setGraphics(GeneLabCore::GraphicsScene* scene);

    signals:

    public slots:

    };

}

#endif // OGREBULLETWORLD_H
