#include "entitiesengine.h"

#include <QDebug>

#include "entity.h"
#include "brain.h"
#include "sensor.h"
#include "modifier.h"

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
//    foreach(Entity* e, entities) {
//        // step brains
//        if(e->getBrain() != NULL)
//            e->getBrain()->step();
//    }
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
