#include "ogrebulletsimulationmanager.h"
#include "graphic/ogreinputmanager.h"
#include "graphic/ogremanager.h"
#include "graphic/defaulteventmanager.h"
#include "physics/bulletmanager.h"

namespace GeneLabOgreBullet {

    OgreBulletSimulationManager::OgreBulletSimulationManager(BulletManager* bulletManager, OgreManager* ogreManager, DefaultEventManager *eventsManager, QObject *parent)
    {
        this->bulletManager = bulletManager;
        this->ogreManager = ogreManager;
        this->eventsManager = eventsManager;
    }

    void OgreBulletSimulationManager::setBulletManager(BulletManager* bulletManager){
        this->bulletManager = bulletManager;
    }

    void OgreBulletSimulationManager::setOgreManager(OgreManager* ogreManager){
        this->ogreManager = ogreManager;
    }

    BulletManager* OgreBulletSimulationManager::getBulletManager() {
        return bulletManager;
    }

    OgreManager* OgreBulletSimulationManager::getOgreManager() {
        return ogreManager;
    }

    void OgreBulletSimulationManager::setup() {
        stepTimer = new QTimer();
        stepTimer->setInterval(1000/60.0); // 30fps
        connect(stepTimer, SIGNAL(timeout()), this, SLOT(update()));
    }

    void  OgreBulletSimulationManager::start()
    {
        stepTimer->start();
    }

    void OgreBulletSimulationManager::stop()
    {
        stepTimer->stop();
    }

    void OgreBulletSimulationManager::update()
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

