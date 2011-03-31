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

        void setPhysics(BulletScene* bullet);
        void setGraphics(OgreScene* ogre);

    signals:

    public slots:
        void setup();

    private:
        BulletScene* bullet;
        OgreScene*   ogre;

    };

}

#endif // OGREBULLETWORLD_H
