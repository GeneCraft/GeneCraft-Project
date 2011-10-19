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
