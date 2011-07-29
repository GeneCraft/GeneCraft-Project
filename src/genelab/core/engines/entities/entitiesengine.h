#ifndef ENTITIESENGINE_H
#define ENTITIESENGINE_H

#include <QList>
#include "genecraftcoreclasses.h"
#include "engine.h"
#include "entities/entity.h"

namespace GeneCraftCore {

/**
 * (c) GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Engine to manage entities.
 *
 * 1) During before step, sensors will stepped.
 * 2) During step, brains will stepped.
 * 3) During after step, modifiers will stepped.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo & Cyprien Huissoud
 */
class EntitiesEngine : public Engine
{
public:
    EntitiesEngine();
    void addEntity(Entity * entity) {
        entity->setAge(0);
        entities.append(entity);
    }

    void removeEntity(Entity* entity) {
        entities.removeAll(entity);
    }

    void removeAndDeleteAllEntities();

    QList<Entity*> getAllEntities() {
        return QList<Entity*>(entities);
    }

    void beforeStep();
    void step();
    void afterStep();

private:
    QList<Entity *> entities;
    int cptBrain;
};
}

#endif // ENTITIESENGINE_H
