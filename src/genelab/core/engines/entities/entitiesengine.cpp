#include "entitiesengine.h"

#include <QDebug>

#include "entity.h"
#include "brain/brain.h"
#include "brain/brainpluggrid.h"
#include "sensors/sensor.h"
#include "modifiers/modifier.h"

#include "widgets/entities/pluggriddesignvisualizer.h"
#include "widgets/entities/pluggridvisualizer.h"

namespace GeneLabCore {
EntitiesEngine::EntitiesEngine()
{
}

void EntitiesEngine::beforeStep()
{
    foreach(Entity* e, entities) {
        // step sensors
        QList<Sensor *> sensors = e->getSensors();
        foreach(Sensor *s, sensors)
            s->step();
    }
}

int cptBrain;
void EntitiesEngine::step()
{
    cptBrain++;
    if(cptBrain%6) // 60/6 brain step per sec so 0.1
        return;

    foreach(Entity* e, entities) {
        // step brains
        if(e->getBrain() != NULL) {
            e->getBrain()->getPlugGrid()->beforeStep();
        }
    }

    foreach(PlugGridVisualizer* viz, gridVisualizers) {
        viz->step();
    }

    foreach(PlugGridDesignVisualizer* vizD, gridDezVisualizers) {
        vizD->step();
    }

    foreach(Entity* e, entities) {
        // step brains
        if(e->getBrain() != NULL) {
            e->getBrain()->step();
        }
    }

    foreach(Entity* e, entities) {
        // step brains
        if(e->getBrain() != NULL) {
            e->getBrain()->getPlugGrid()->afterStep();
        }
    }
}

void EntitiesEngine::afterStep()
{
    foreach(Entity* e, entities) {
        // step modifiers
        QList<Effector *> modifiers = e->getEffectors();
        foreach(Effector* m, modifiers)
            m->step();
    }
}
}
