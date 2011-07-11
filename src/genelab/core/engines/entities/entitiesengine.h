#ifndef ENTITIESENGINE_H
#define ENTITIESENGINE_H

#include <QList>
#include "genelabcoreclasses.h"
#include "engine.h"

namespace GeneLabCore {

/**
 * (c) GeneLab 2011, Aurelien Da Campo & Cyprien Huissoud
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
        entities.append(entity);
    }

    void removeEntity(Entity* entity) {
        entities.removeAll(entity);
    }

    QList<Entity*> getAllEntities() {
        return QList<Entity*>(entities);
    }

    void addPlugGridVisualizer(PlugGridVisualizer* viz) {
        this->gridVisualizers.append(viz);
    }

    void addPlugGridDezVisualizer(PlugGridDesignVisualizer* viz) {
        this->gridDezVisualizers.append(viz);
    }

    void beforeStep();
    void step();
    void afterStep();

private:
    QList<Entity *> entities;
    QList<PlugGridVisualizer*> gridVisualizers;
    QList<PlugGridDesignVisualizer*> gridDezVisualizers;
    int cptBrain;
};
}

#endif // ENTITIESENGINE_H
