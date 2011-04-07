#ifndef OGREBULLETSIMULATIONMANAGER_H
#define OGREBULLETSIMULATIONMANAGER_H

#include "classes.h"
#include "simulation/simulationmanager.h"
#include <QObject>

namespace GeneLabOgreBullet {

    class OgreBulletSimulationManager : public GeneLabCore::SimulationManager
    {
        Q_OBJECT
    public:

        OgreBulletSimulationManager(QObject *parent = 0) : GeneLabCore::SimulationManager(parent) {}

        OgreBulletSimulationManager(BulletManager* bulletManager, OgreManager* ogreManager, DefaultEventManager *eventsManager, QObject *parent = 0);

        void setBulletManager(BulletManager* bulletManager);
        void setOgreManager(OgreManager* ogreManager);

        BulletManager* getBulletManager();
        OgreManager* getOgreManager();

    signals:

    public slots:
        void setup();

        // added by ADC
        // the world manager the time
        void start();
        void stop();
        void update();

    private:
        BulletManager* bulletManager;
        OgreManager*   ogreManager;
        DefaultEventManager *eventsManager;


        // Execution timer
        QTimer *stepTimer;
    };

}

#endif // OGREBULLETSIMULATIONMANAGER_H
