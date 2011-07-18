#include "treeshapestats.h"

#include "statisticsstorage.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"
#include "body/bone.h"
#include "body/fixation.h"
#include "body/treeshape.h"
#include "entity.h"

namespace GeneLabCore{

TreeShapeStats::TreeShapeStats(StatisticsStorage * statsStorage, TreeShape * treeshape) :
    StatisticsProvider(statsStorage), treeshape(treeshape)
{
    treeshapeVerticalHeight = new Statistic("Treeshape Vertical Height","m");
    statsStorage->registerStat("Treeshape Vertical Height",treeshapeVerticalHeight);

    treeshapeBones = new Statistic("Treeshape Bones","bones");
    statsStorage->registerStat("Treeshape Bones",treeshapeBones);

    treeshapeBonesLength = new Statistic("Treeshape Bones Length","m");
    statsStorage->registerStat("Treeshape Bones Length",treeshapeBonesLength);

    treeshapeWeight = new Statistic("Treeshape Weight","kg");
    statsStorage->registerStat("Treeshape Weight",treeshapeWeight);

    treeshapeNbSensors = new Statistic("Treeshape Nb Sensors","sensors");
    statsStorage->registerStat("Treeshape Nb Sensors",treeshapeNbSensors);

    treeshapeNbEffectors = new Statistic("Treeshape Nb Effectors","effectors");
    statsStorage->registerStat("Treeshape Nb Effectors",treeshapeNbEffectors);
}

void TreeShapeStats::recursiveUpdate(Bone *b)
{
    // TREESHAPE BONES LENGTH
    length += b->getLength();

    // TREESHAPE BONES NUMBER
    nbBones++;

    // TREESHAPE WEIGHT
    weight += 1.0/b->getRigidBody()->getInvMass(); // (compound bone + fix)

    // TREESHAPE VERTICAL HEIGHT
    // Bone.rigidBody == Bone.endFixation.rigidBody (CompoundShape)
    // compute local origin of the end fixation
    btVector3 fixLocalOrigin(0,b->getLength()*0.5 + b->getEndFixation()->getRadius(),0);
    btQuaternion boneRot = b->getRigidBody()->getWorldTransform().getRotation();
    fixLocalOrigin.rotate(boneRot.getAxis(),boneRot.getAngle());

    // Compute global origin (just Y) of the end fixation
    btScalar y = b->getEndFixation()->getRigidBody()->getWorldTransform().getOrigin().y() + fixLocalOrigin.y();

    if(y < minHeightY)
       minHeightY = y;

    if(y > maxHeightY)
       maxHeightY = y;

    // RECURCIVE BROWSING
    foreach (Bone *b, b->getEndFixation()->getBones())
        recursiveUpdate(b);
}

void TreeShapeStats::step()
{
    // TREESHAPE BONES LENGTH
    length = 0.0;

    // TREESHAPE BONES NUMBER
    nbBones = 0;

    // TREESHAPE WEIGHT
    weight = 1.0/treeshape->getRoot()->getRigidBody()->getInvMass();

    // TREESHAPE VERTICAL HEIGHT
    // Algo : find the heighter and the lower fixation in y axis, height = max - min
    minHeightY = maxHeightY = treeshape->getRoot()->getRigidBody()->getWorldTransform().getOrigin().y();

    foreach (Bone *b, treeshape->getRoot()->getBones())
        recursiveUpdate(b);

    // UPDATE VALUES
    treeshapeBones->setValue(nbBones);
    treeshapeBonesLength->setValue(length);
    treeshapeWeight->setValue(weight);
    treeshapeVerticalHeight->setValue(maxHeightY - minHeightY);
    treeshapeNbSensors->setValue(treeshape->getRoot()->getEntity()->getSensors().count());
    treeshapeNbEffectors->setValue(treeshape->getRoot()->getEntity()->getEffectors().count());
}


}
