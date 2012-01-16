/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

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
