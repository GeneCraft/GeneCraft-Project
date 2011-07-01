#ifndef ENTITYWEIGHTSTAT_H
#define ENTITYWEIGHTSTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"

namespace GeneLabCore{

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
