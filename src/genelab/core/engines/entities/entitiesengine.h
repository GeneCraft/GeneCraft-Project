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
    Q_OBJECT
public:
    EntitiesEngine();
    inline void addEntity(Entity * entity) { entities.append(entity); }

public slots:
    void beforeStep();
    void step();
    void afterStep();

private:
    QList<Entity *> entities;
};
}

#endif // ENTITIESENGINE_H
