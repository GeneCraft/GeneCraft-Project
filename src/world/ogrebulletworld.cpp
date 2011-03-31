#include "ogrebulletworld.h"

namespace GeneLabOgreBullet {
    using namespace GeneLabCore;
    OgreBulletWorld::OgreBulletWorld(QObject *parent) :
        World(parent)
    {
    }


    void OgreBulletWorld::setPhysics(BulletScene* scene) {
        this->bullet = scene;
    }

    void OgreBulletWorld::setGraphics(OgreScene* scene) {
        this->ogre = scene;
    }

    void OgreBulletWorld::setup() {

    }
}
