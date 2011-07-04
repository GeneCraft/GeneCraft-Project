#ifndef ENTITYWEIGHTSTAT_H
#define ENTITYWEIGHTSTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"

namespace GeneLabCore{

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Statistics used to know the total weight of an entity.
 *
 * Unit : kg
 *
 * @version 1.0 | July 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class EntityWeightStat : public Statistic
{
public:

    EntityWeightStat(Entity * entity);
    void update();

protected:

    Entity * entity;
    void recurciveUpdate(Bone *b);

};

}
#endif // ENTITYWEIGHTSTAT_H
