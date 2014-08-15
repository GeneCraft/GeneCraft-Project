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

#ifndef ENTITIESENGINE_H
#define ENTITIESENGINE_H

#include <QList>
#include "genecraftcoreclasses.h"
#include "engine.h"
#include "entities/entity.h"

namespace GeneCraftCore {

/**
 * @brief Engine to manage entities.
 * 1) During before step, sensors will stepped.
 * 2) During step, brains will stepped.
 * 3) During after step, modifiers will stepped.
 *
 *
 */
class EntitiesEngine : public Engine
{
public:
    /**
     * @brief Create the entity engine
     *
     */
    EntitiesEngine();
    /**
     * @brief add an entity to the list of actives entity
     *
     * @param entity
     */
    void addEntity(Entity * entity);
    /**
     * @brief remove an entity of the list of actives entity
     *
     * @param entity
     */
    void removeEntity(Entity* entity);
    /**
     * @brief remove and delete all actives entity
     *
     */
    void removeAndDeleteAllEntities();
    /**
     * @brief return all actives entity
     *
     */
    QList<Entity*> getAllEntities();
    /**
     * @brief do all initial stuff about entity (i.e. increment age,
     update statistics and if it's a neural step, update sensors informations)
     *
     */
    void beforeStep();
    /**
     * @brief do all main stuff about entity (i.e. brain step if neural step)
     *
     */
    void step();
    /**
     * @brief do all the closing stuff about entity (i.e. effector update)
     *
     */
    void afterStep();

private:
    QList<Entity *> entities; /**< the list of all entity */
};
}

#endif // ENTITIESENGINE_H
