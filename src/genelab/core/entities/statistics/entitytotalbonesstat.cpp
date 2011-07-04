#include "entitytotalbonesstat.h"

#include "entity.h"
#include "body/treeshape.h"
#include "body/bone.h"
#include "body/fixation.h"

namespace GeneLabCore{

EntityTotalBonesStat::EntityTotalBonesStat(Entity *entity) : entity(entity)
{
    update();
    updateEachStep = false;
}

void EntityTotalBonesStat::recurciveUpdate(Bone *b)
{
    value += b->getEndFixation()->getBones().size();

    foreach (Bone *b, b->getEndFixation()->getBones())
        recurciveUpdate(b);
}

void EntityTotalBonesStat::update()
{
    value = entity->getShape()->getRoot()->getBones().size();

    foreach (Bone *b, entity->getShape()->getRoot()->getBones())
        recurciveUpdate(b);
}

}
