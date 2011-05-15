#include "SimulationManager.h"
#include "graphic/ogreinputmanager.h"
#include "graphic/ogremanager.h"
#include "graphic/eventmanager.h"
#include "physics/bulletmanager.h"
#include "engine/engine.h"

#include <QTimer>

namespace GeneLabCore {

    SimulationManager::SimulationManager(QList<GeneLabCore::Engine*> engines, QObject *parent)
    {
        this->engines.append(engines);
    }

    void SimulationManager::setup() {
        stepTimer = new QTimer();
        stepTimer->setInterval(1000/60.0); // 30fps
        connect(stepTimer, SIGNAL(timeout()), this, SLOT(update()));
    }

    void SimulationManager::addEngine(GeneLabCore::Engine *engine) {
        if(!this->engines.contains(engine))
            this->engines.append(engine);
    }

    void SimulationManager::removeEngine(GeneLabCore::Engine *engine) {
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
        foreach(GeneLabCore::Engine* e, engines) {
            e->beforeStep();
        }
        foreach(GeneLabCore::Engine* e, engines) {
            e->step();
        }
        foreach(GeneLabCore::Engine* e, engines) {
            e->afterStep();
        }
    }
}

