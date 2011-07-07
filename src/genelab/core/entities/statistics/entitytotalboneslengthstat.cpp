//#include "entitytotalboneslengthstat.h"

//#include "entity.h"
//#include "body/treeshape.h"
//#include "body/bone.h"
//#include "body/fixation.h"

//namespace GeneLabCore{

//EntityTotalBonesLengthStat::EntityTotalBonesLengthStat(Entity *entity) : entity(entity)
//{
//    // Info
//    name = "Body total bones length";
//    unit = "m";

//    updateEachStep = false;
//    updateWhenValueIsRequested = true;
//}

//void EntityTotalBonesLengthStat::recurciveUpdate(Bone *b)
//{
//    value += b->getLength();

//    foreach (Bone *b, b->getEndFixation()->getBones())
//        recurciveUpdate(b);
//}

//void EntityTotalBonesLengthStat::update()
//{
//    value = 0.0;

//    foreach (Bone *b, entity->getShape()->getRoot()->getBones())
//        recurciveUpdate(b);
//}

//}
