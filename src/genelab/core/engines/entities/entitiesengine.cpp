<<<<<<< .mine
#include "entitiesengine.h"

#include "entity.h"
#include "brain/brain.h"
#include "brain/brainpluggrid.h"
#include "sensors/sensor.h"
#include "effectors/effector.h"

#include "widgets/entities/pluggriddesignvisualizer.h"
#include "widgets/entities/pluggridvisualizer.h"

namespace GeneLabCore {
EntitiesEngine::EntitiesEngine()
{
    cptBrain = 0;
}

void EntitiesEngine::beforeStep()
{
    foreach(Entity* e, entities) {
        e->incrAge();

        // step statistics
        e->updadeStatistics();

        if(e->getAge() % e->getBrain()->getFrequency())
            continue;


        // step sensors
        foreach(Sensor *s, e->getSensors()) {

            s->step();

        }

    }
}

void EntitiesEngine::step()
{
    foreach(PlugGridVisualizer* viz, gridVisualizers) {
        viz->step();
    }

    foreach(PlugGridDesignVisualizer* vizD, gridDezVisualizers) {
        vizD->step();
    }

    foreach(Entity* e, entities) {
        if(e->getAge() % e->getBrain()->getFrequency())
            continue;

        e->getBrain()->step();
    }
}

void EntitiesEngine::afterStep()
{
    foreach(Entity* e, entities) {

        if(e->getAge() % e->getBrain()->getFrequency())
            continue;

        // step modifiers
        QList<Effector *> modifiers = e->getEffectors();
        foreach(Effector* m, modifiers)
            m->step();
    }
}

void EntitiesEngine::removeAndDeleteAllEntities() {

    while(entities.size() != 0){

        Entity * old = entities.takeFirst();
        delete old;
    }
}

}
=======
#include "entitiesengine.h"

#include "entity.h"
#include "brain/brain.h"
#include "brain/brainpluggrid.h"
#include "sensors/sensor.h"
#include "effectors/effector.h"

#include "widgets/entities/pluggriddesignvisualizer.h"
#include "widgets/entities/pluggridvisualizer.h"

namespace GeneCraftCore {
EntitiesEngine::EntitiesEngine()
{
    cptBrain = 0;
}

void EntitiesEngine::beforeStep()
{
    foreach(Entity* e, entities) {

        // step statistics
        e->updadeStatistics();

        if(e->getAge() % e->getBrain()->getFrequency())
            continue;


        // step sensors
        foreach(Sensor *s, e->getSensors()) {

            s->step();

        }

    }
}

void EntitiesEngine::step()
{
    foreach(Entity* e, entities) {
        // step brains
        if(e->getBrain() != NULL) {
            e->getBrainActivityStat()->setValue(1./e->getBrain()->getFrequency());
            e->incrAge();

            if(e->getAge() % e->getBrain()->getFrequency())
                continue;

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
        if(e->getAge() % e->getBrain()->getFrequency())
            continue;

        if(e->getBrain() != NULL) {
            e->getBrain()->step();
        }
    }

    foreach(Entity* e, entities) {
        if(e->getAge() % e->getBrain()->getFrequency())
            continue;

        // step brains
        if(e->getBrain() != NULL) {
            e->getBrain()->getPlugGrid()->afterStep();
        }
    }
}

void EntitiesEngine::afterStep()
{
    foreach(Entity* e, entities) {

        if(e->getAge() % e->getBrain()->getFrequency())
            continue;

        // step modifiers
        QList<Effector *> modifiers = e->getEffectors();
        foreach(Effector* m, modifiers)
            m->step();
    }
}

void EntitiesEngine::removeAndDeleteAllEntities() {

    while(entities.size() != 0){

        Entity * old = entities.takeFirst();
        delete old;
    }
}

}
>>>>>>> .r438
