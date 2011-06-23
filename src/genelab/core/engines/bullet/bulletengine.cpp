#include "bulletengine.h"
#include <QDebug>

namespace GeneLabCore {
    using namespace Ogre;

    BulletEngine::BulletEngine(QObject *parent) :
        Engine(parent)
    {
        physicsEnable = true;
    }

    void BulletEngine::step() {
        if(physicsEnable) {
            foreach(btDynamicsWorld* world, worldList)
                world->stepSimulation(1.0/60., 10, 1/240.);
        }
    }
}
