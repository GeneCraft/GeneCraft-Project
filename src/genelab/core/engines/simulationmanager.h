#ifndef SimulationManager_H
#define SimulationManager_H

#include "genelabcoreclasses.h"
#include <QObject>

#include <QTimer>

namespace GeneLabCore {

    class SimulationManager : QObject
    {
        Q_OBJECT

    public:

        SimulationManager(QObject *parent = 0);
        SimulationManager(QList<Engine*> engines, QObject *parent = 0);


        // TODO
        void addEngine(Engine *engine);
        void removeEngine(Engine *engine);

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
