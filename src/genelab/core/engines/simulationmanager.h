#ifndef SimulationManager_H
#define SimulationManager_H

#include "genecraftcoreclasses.h"
#include <QObject>
#include <QMap>

#include <QTimer>
#include <QTime>

namespace GeneCraftCore {

    class SimulationManager : public QObject
    {
        Q_OBJECT

    public:

        SimulationManager(QObject *parent = 0);
        SimulationManager(QMap<QString, Engine*>, QObject *parent = 0);

        void addEngine(QString name, Engine *engine);
        void removeEngine(QString name);

        inline int getPhysicsFreq()
        {
            return stepBySec;
        }

    signals:

    public slots:

        // init timer
        void setup();

        // the world manager the time
        void start();
        void stop();
        bool toggle();
        void setPhysicsFreq(int stepBySec);
        void update();
        void renderUpdate();

        void resetNbSteps();

    private:
        QMap<QString, Engine*> engines;
        Engine* renderEngine;
        Engine* translationEngine;
        Engine* eventsManager;

        // Execution timer
        int nbSteps;
        int stepBySec;
        QTimer *stepTimer;
        QTimer *renderTimer;
    };

}

#endif // SimulationManager_H
