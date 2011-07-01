#ifndef ENTITYHEIGHTSTAT_H
#define ENTITYHEIGHTSTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"

namespace GeneLabCore{

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
