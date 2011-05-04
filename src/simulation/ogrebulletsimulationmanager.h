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

        // TODO remove all engines
        OgreBulletSimulationManager(BulletManager* bulletManager, OgreManager* ogreManager, EventManager *eventsManager, QObject *parent = 0);

        // TODO delete
        void setBulletManager(BulletManager* bulletManager);
        void setOgreManager(OgreManager* ogreManager);
        BulletManager *getBulletManager();
        OgreManager *getOgreManager();

        // TODO
        // void addEngine(GeneLabCore::Engine *engine);
        // void removeEngine(GeneLabCore::Engine *engine);

    signals:

    public slots:

        // init timer
        void setup();

        // the world manager the time
        void start();
        void stop();
        void update();

    private:

        // Engines
        // TODO : replace by a QList of subclasse Engine
        // QList<GeneLabCore::Engine *> engines;
        BulletManager *bulletManager;
        OgreManager *ogreManager;
        EventManager *eventsManager;

        // Execution timer
        QTimer *stepTimer;
    };

}

#endif // OGREBULLETSIMULATIONMANAGER_H
