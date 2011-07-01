#include "entityheightstat.h"

#include "entity.h"
#include "body/treeshape.h"
#include "body/bone.h"
#include "body/fixation.h"

namespace GeneLabCore{

EntityHeightStat::EntityHeightStat(Entity *entity) : entity(entity)
{
    update();
}

void EntityHeightStat::recurciveUpdate(Bone *b)
{
    btScalar y = b->getEndFixation()->getRigidBody()->getWorldTransform().getOrigin().y();

    if(y < minY)
       minY = y;

    if(y > maxY)
       maxY = y;

    foreach (Bone *b, b->getEndFixation()->getBones())
        recurciveUpdate(b);
}

void EntityHeightStat::update()
{
    // Algo : find the heighter and the lower fixation in y axis, height = max - min

    minY = maxY = entity->getShape()->getRoot()->getRigidBody()->getWorldTransform().getOrigin().y();

    foreach (Bone *b, entity->getShape()->getRoot()->getBones())
        recurciveUpdate(b);

    // update value
    value = maxY - minY;
}

}
