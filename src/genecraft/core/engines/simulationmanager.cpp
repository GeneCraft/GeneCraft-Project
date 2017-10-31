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

#include "simulationmanager.h"

#include "engine.h"
#include <QTimer>
#include <ctime>


namespace GeneCraftCore {

    SimulationManager::SimulationManager(QMap<QString, Engine*> engines, QObject *)
    {
        this->engines = engines;
        this->renderEngine      = engines.find("Ogre").value();
        //this->translationEngine = engines.find("BulletOgre").value();
        this->eventsManager     = engines.find("Events").value();

        this->engines.remove("Ogre");
        //this->engines.remove("OgreBullet");
        this->engines.remove("EventsManager");

        this->stepBySec = 60;
        this->nbSteps = 0;
        fitness = NULL;
    }

    void SimulationManager::setup() {
        stepTimer = new QTimer();
        renderTimer = new QTimer();
        renderTimer->setInterval(1000/40); // 40fps
        stepTimer->setInterval(1000/stepBySec); // 60 frames by sec
        connect(stepTimer, SIGNAL(timeout()), this, SLOT(update()));
        connect(renderTimer, SIGNAL(timeout()), this, SLOT(renderUpdate()));
        renderTimer->start();
    }

    void SimulationManager::addEngine(QString name, Engine *engine) {
        if(!this->engines.contains(name))
            this->engines.insert(name, engine);
    }

    void SimulationManager::removeEngine(QString name) {
        this->engines.remove(name);
    }

    void  SimulationManager::start()
    {
        stepTimer->start();
    }

    void SimulationManager::stop()
    {
        stepTimer->stop();
    }

    bool SimulationManager::status() {
        return stepTimer->isActive();
    }

    void SimulationManager::setStatus(bool st) {
        if(st)
            stepTimer->start();
        else
            stepTimer->stop();
    }

    bool SimulationManager::toggle() {
        if(stepTimer->isActive()) {
            stepTimer->stop();
        } else {
            stepTimer->start();
        }

        return stepTimer->isActive();
    }

    void SimulationManager::resetNbSteps() {
        nbSteps = 0;
    }

    void SimulationManager::update()
    {
        nbSteps++;

        // beforeStep
        foreach(Engine* e, engines)
            e->beforeStep();

        // step
        foreach(Engine* e, engines)
            e->step();

        // after step
        foreach(Engine* e, engines)
            e->afterStep();

        if(fitness)
            fitness->step();

    }

    void SimulationManager::renderUpdate() {

        // beforeStep
        this->eventsManager->beforeStep();
        //this->translationEngine->beforeStep();
        this->renderEngine->beforeStep();

        // step
        this->eventsManager->step();
        //this->translationEngine->step();
        this->renderEngine->step();

        // after step
        this->eventsManager->afterStep();
        //this->translationEngine->afterStep();
        this->renderEngine->afterStep();

        // Update some graphical widgets
        foreach(GraphicalWidget* wi, graphWidgets) {
            wi->step();
        }

    }

    void SimulationManager::setPhysicsFreq(int stepBySec) {
        this->stepBySec = stepBySec;
        if(stepBySec < 1)
            stepBySec = 1;
        this->stepTimer->setInterval(1000/stepBySec);
    }

    void SimulationManager::addGraphicalWidget(GraphicalWidget *widget) {
        this->graphWidgets.append(widget);
    }
}

