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

#include "entitiesengine.h"

#include "entity.h"
#include "brain/brain.h"
#include "brain/brainpluggrid.h"
#include "sensors/sensor.h"
#include "effectors/effector.h"
#include "entities/entity.h"

namespace GeneCraftCore {

    EntitiesEngine::EntitiesEngine()
    {
    }

    void EntitiesEngine::addEntity(Entity * entity) {
        entity->setAge(0);
        entities.append(entity);
    }

    void EntitiesEngine::removeEntity(Entity* entity) {
        entities.removeAll(entity);
    }

    QList<Entity*> EntitiesEngine::getAllEntities() {
        return QList<Entity*>(entities);
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
