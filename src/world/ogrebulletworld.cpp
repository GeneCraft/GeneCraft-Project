#include "ogrebulletworld.h"

namespace GeneLabOgreBullet {
    using namespace GeneLabCore;

    OgreBulletWorld::OgreBulletWorld(QObject *parent) :
            World(parent)
    {
    }

    OgreBulletWorld::OgreBulletWorld(BulletManager* bulletManager, OgreManager* ogreManager, DefaultEventManager *eventsManager, QObject *parent):
            World(parent)
    {
        this->bulletManager = bulletManager;
        this->ogreManager = ogreManager;
        this->eventsManager = eventsManager;
    }

    void OgreBulletWorld::setBulletManager(BulletManager* bulletManager){
        this->bulletManager = bulletManager;
    }

    void OgreBulletWorld::setOgreManager(OgreManager* ogreManager){
        this->ogreManager = ogreManager;
    }

    BulletManager* OgreBulletWorld::getBulletManager() {
        return bulletManager;
    }

    OgreManager* OgreBulletWorld::getOgreManager() {
        return ogreManager;
    }

    void OgreBulletWorld::setup() {
        stepTimer = new QTimer();
        stepTimer->setInterval(1000/30); // 30fps
        connect(stepTimer, SIGNAL(timeout()), this, SLOT(update()));
    }

    void  OgreBulletWorld::start()
    {
        stepTimer->start();
    }

    void OgreBulletWorld::stop()
    {
        stepTimer->stop();
    }

    void OgreBulletWorld::update()
    {
        eventsManager->beforeStep();
        ogreManager->beforeStep();
        bulletManager->beforeStep();

        eventsManager->step();
        ogreManager->step();
        bulletManager ->step();

        eventsManager->afterStep();
        ogreManager->afterStep();
        bulletManager->afterStep();
    }
}
