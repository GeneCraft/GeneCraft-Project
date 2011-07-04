#ifndef ENTITYHEIGHTSTAT_H
#define ENTITYHEIGHTSTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"

namespace GeneLabCore{

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Statistics used to know the height of an entity. The height is the distance (only on Y axis)
 * between the position of the heightest fixation and the position of the lowest fixation.
 *
 * Unit : meters
 *
 * trick : height = lowestFixation.y - heightestFixation.y
 *
 * @version 1.0 | July 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class EntityHeightStat : public Statistic
{
public:

    EntityHeightStat(Entity * entity);
    void update();

protected:

    Entity * entity;
    float minY, maxY;
    void recurciveUpdate(Bone *b);

};

}
#endif // ENTITYHEIGHTSTAT_H
