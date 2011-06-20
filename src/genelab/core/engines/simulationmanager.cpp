#include "simulationmanager.h"

#include "engine.h"

#include <QTimer>
#include <ctime>

namespace GeneLabCore {

    SimulationManager::SimulationManager(QMap<QString, Engine*> engines, QObject *parent)
    {
        this->engines = engines;
    }

    void SimulationManager::setup() {
        stepTimer = new QTimer();
        stepTimer->setInterval(1000/60.0); // 30fps
        connect(stepTimer, SIGNAL(timeout()), this, SLOT(update()));
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

    void SimulationManager::update()
    {
        foreach(Engine* e, engines)
            e->beforeStep();

        foreach(Engine* e, engines)
            e->step();

        foreach(Engine* e, engines)
            e->afterStep();
    }
}

