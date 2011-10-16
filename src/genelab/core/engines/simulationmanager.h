#ifndef SimulationManager_H
#define SimulationManager_H

#include "genecraftcoreclasses.h"
#include "widgets/plot/fitnessplot.h"
#include "widgets/graphicalwidget.h"
#include <QObject>
#include <QMap>

#include <QTimer>
#include <QTime>
#include <QMutex>

namespace GeneCraftCore {

    class SimulationManager : public QObject
    {
        Q_OBJECT

    public:

        SimulationManager(QObject *parent = 0);
        SimulationManager(QMap<QString, Engine*>, QObject *parent = 0);

        void addEngine(QString name, Engine *engine);
        void addGraphicalWidget(GraphicalWidget* widget);
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
        bool status();
        void setStatus(bool status);
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

        QList<GraphicalWidget*> graphWidgets;

        // Execution timer
        int nbSteps;
        int stepBySec;
        QTimer *stepTimer;
        QTimer *renderTimer;
    public:
        FitnessPlot* fitness;
    };

}

#endif // SimulationManager_H
