#ifndef SimulationManager_H
#define SimulationManager_H

#include "classes.h"
#include "simulation/simulationmanager.h"
#include <QObject>

#include <QTimer>

namespace GeneLabCore {

    class SimulationManager : QObject
    {
        Q_OBJECT

    public:

        SimulationManager(QObject *parent = 0);
        SimulationManager(QList<GeneLabCore::Engine*> engines, QObject *parent = 0);


        // TODO
        void addEngine(GeneLabCore::Engine *engine);
        void removeEngine(GeneLabCore::Engine *engine);

    signals:

    public slots:

        // init timer
        void setup();

        // the world manager the time
        void start();
        void stop();
        void update();

    private:
        QList<GeneLabCore::Engine*> engines;

        // Execution timer
        QTimer *stepTimer;
    };

}

#endif // SimulationManager_H
