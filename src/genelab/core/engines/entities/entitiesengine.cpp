#include "entitiesengine.h"

#include <QDebug>

#include "entity.h"
#include "brain/brain.h"
#include "brain/brainpluggrid.h"
#include "sensors/sensor.h"
#include "modifiers/modifier.h"

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

void EntitiesEngine::step()
{
    foreach(Entity* e, entities) {
        // step brains
        if(e->getBrain() != NULL) {
            e->getBrain()->getPlugGrid()->beforeStep();
            e->getBrain()->step();
            e->getBrain()->getPlugGrid()->afterStep();
        }
    }
}

void EntitiesEngine::afterStep()
{
    foreach(Entity* e, entities) {
        // step modifiers
        QList<Modifier *> modifiers = e->getModifiers();
        foreach(Modifier* m, modifiers)
            m->step();
    }
}
}
