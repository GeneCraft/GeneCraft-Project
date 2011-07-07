//#include "entityweightstat.h"

//#include "entity.h"
//#include "body/treeshape.h"
//#include "body/bone.h"
//#include "body/fixation.h"

//namespace GeneLabCore{

//EntityWeightStat::EntityWeightStat(Entity *entity) : entity(entity)
//{
//    // Info
//    name = "Body weight";
//    unit = "kg";

//    // Optimization : Only update when the value is needed
//    updateWhenValueIsRequested = true;
//    updateEachStep = false;
//}

//void EntityWeightStat::recurciveUpdate(Bone *b)
//{
//    // bone + end fixation masses
//    value += 1.0/b->getRigidBody()->getInvMass();

//    // add recurcively all bone masses
//    foreach (Bone *b, b->getEndFixation()->getBones())
//        recurciveUpdate(b);
//}

//void EntityWeightStat::update()
//{
//    // root fixation mass
//    value = 1.0/entity->getShape()->getRoot()->getRigidBody()->getInvMass();

//    // add recurcively all bone masses
//    foreach (Bone *b, entity->getShape()->getRoot()->getBones())
//        recurciveUpdate(b);
//}

//}
