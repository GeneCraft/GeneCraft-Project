#include "simulationmanager.h"

#include "core/engine/ogremanager.h"
#include "core/engine/eventmanager.h"
#include "core/engine/bulletmanager.h"
#include "core/engine/engine.h"

#include <QTimer>

namespace GeneLabCore {

    SimulationManager::SimulationManager(QList<Engine*> engines, QObject *parent)
    {
        this->engines.append(engines);
    }

    void SimulationManager::setup() {
        stepTimer = new QTimer();
        stepTimer->setInterval(1000/60.0); // 30fps
        connect(stepTimer, SIGNAL(timeout()), this, SLOT(update()));
    }

    void SimulationManager::addEngine(Engine *engine) {
        if(!this->engines.contains(engine))
            this->engines.append(engine);
    }

    void SimulationManager::removeEngine(Engine *engine) {
        this->engines.removeOne(engine);
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
        foreach(Engine* e, engines) {
            e->beforeStep();
        }
        foreach(Engine* e, engines) {
            e->step();
        }
        foreach(Engine* e, engines) {
            e->afterStep();
        }
    }
}

