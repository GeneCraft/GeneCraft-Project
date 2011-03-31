#include "ogrebulletworld.h"
#include "physics/physicsscene.h"
#include "graphic/graphicsscene.h"

namespace GeneLabOgreBullet {
    using namespace GeneLabCore;
    OgreBulletWorld::OgreBulletWorld(QObject *parent) :
        World(parent)
    {
    }


    void OgreBulletWorld::setPhysics(PhysicsScene* scene) {
    }

    void OgreBulletWorld::setGraphics(GraphicsScene* scene) {
    }
}
