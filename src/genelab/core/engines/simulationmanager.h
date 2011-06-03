#ifndef SimulationManager_H
#define SimulationManager_H

#include "genelabcoreclasses.h"
#include <QObject>
#include <QMap>

#include <QTimer>

namespace GeneLabCore {

    class SimulationManager : QObject
    {
        Q_OBJECT

    public:

        SimulationManager(QObject *parent = 0);
        SimulationManager(QMap<QString, Engine*>, QObject *parent = 0);


        // TODO
        void addEngine(QString name, Engine *engine);
        void removeEngine(QString name);

    signals:

    public slots:

        // init timer
        void setup();

        // the world manager the time
        void start();
        void stop();
        void update();

    private:
        QMap<QString, Engine*> engines;

        // Execution timer
        QTimer *stepTimer;
    };

}

#endif // SimulationManager_H
