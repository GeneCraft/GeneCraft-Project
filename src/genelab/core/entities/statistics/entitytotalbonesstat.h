#ifndef ENTITYTOTALBONESSTAT_H
#define ENTITYTOTALBONESSTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"

namespace GeneLabCore{

class EntityTotalBonesStat : public Statistic
{
public:

    EntityTotalBonesStat(Entity * entity);
    void update();

protected:

    Entity * entity;
    void recurciveUpdate(Bone *b);

};

}

#endif // ENTITYTOTALBONESSTAT_H
