#include "simulationmanager.h"

#include "engine.h"

#include <QTimer>
#include <ctime>

namespace GeneLabCore {

    SimulationManager::SimulationManager(QMap<QString, Engine*> engines, QObject *parent)
    {
        this->engines = engines;
        this->renderEngine = engines.find("Ogre").value();
        this->translationEngine = engines.find("BulletOgre").value();
        this->engines.remove("Ogre");
        this->engines.remove("OgreBullet");
        this->stepBySec = 60;
        this->nbStep = 0;
    }

    void SimulationManager::setup() {
        stepTimer = new QTimer();
        renderTimer = new QTimer();
        renderTimer->setInterval(1000/40); // 30fps
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

    void SimulationManager::toggle() {
        if(stepTimer->isActive()) {
            stepTimer->stop();
        } else {
            stepTimer->start();
        }
    }

    void SimulationManager::update()
    {
        nbStep++;

        foreach(Engine* e, engines)
            e->beforeStep();

        foreach(Engine* e, engines)
            e->step();

        foreach(Engine* e, engines)
            e->afterStep();
    }

    void SimulationManager::renderUpdate() {
        this->translationEngine->beforeStep();
        this->translationEngine->step();
        this->translationEngine->afterStep();
        this->renderEngine->beforeStep();
        this->renderEngine->step();
        this->renderEngine->afterStep();
    }

    void SimulationManager::setFreq(int stepBySec) {
        this->stepBySec = stepBySec;
        if(stepBySec < 0 )
            stepBySec = 0;
        this->stepTimer->setInterval(1000/(stepBySec+1));
    }
}

