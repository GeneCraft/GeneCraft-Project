#include "bulletengine.h"
#include <QDebug>

namespace GeneLabCore {
    using namespace Ogre;

    BulletEngine::BulletEngine(QObject *parent) :
        Engine(parent)
    {
        physicsEnable = false;
    }

    void BulletEngine::step() {
        if(physicsEnable) {
            foreach(btDynamicsWorld* world, worldList)
                world->stepSimulation(1/60.0, 10);
        }
    }
}
