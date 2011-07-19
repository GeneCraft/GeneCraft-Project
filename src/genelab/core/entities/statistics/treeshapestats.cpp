#include "treeshapestats.h"

#include "statisticsstorage.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"
#include "body/bone.h"
#include "body/fixation.h"
#include "body/treeshape.h"
#include "entity.h"

#include "effectors/effector.h"
#include "effectors/rotationalmotorseffector.h"

namespace GeneLabCore{

TreeShapeStats::TreeShapeStats(StatisticsStorage * statsStorage, TreeShape * treeshape) :
    StatisticsProvider(statsStorage), treeshape(treeshape)
{
    treeshapeVerticalHeight = new Statistic("bodyHeight","m");
    statsStorage->registerStat(treeshapeVerticalHeight->getName(),treeshapeVerticalHeight);

    treeshapeBones = new Statistic("bodyBones","bones / fix");
    statsStorage->registerStat(treeshapeBones->getName(),treeshapeBones);
    connect(treeshapeBones, SIGNAL(reseted()), this, SLOT(reset()));

    treeshapeBonesLength = new Statistic("bodyLength","m / bones");
    statsStorage->registerStat(treeshapeBonesLength->getName(),treeshapeBonesLength);
    connect(treeshapeBonesLength, SIGNAL(reseted()), this, SLOT(reset()));

    treeshapeWeight = new Statistic("bodyWeight","kg / bones");
    statsStorage->registerStat(treeshapeWeight->getName(),treeshapeWeight);
    connect(treeshapeWeight, SIGNAL(reseted()), this, SLOT(reset()));

    treeshapeNbSensors = new Statistic("bodySensors","sensors / fix");
    statsStorage->registerStat(treeshapeNbSensors->getName(),treeshapeNbSensors);
    connect(treeshapeNbSensors, SIGNAL(reseted()), this, SLOT(reset()));

    treeshapeNbEffectors = new Statistic("bodyEffectors","effectors / (bone, fix)");
    statsStorage->registerStat(treeshapeNbEffectors->getName(),treeshapeNbEffectors);
    connect(treeshapeNbEffectors, SIGNAL(reseted()), this, SLOT(reset()));

    this->reset();
}

void TreeShapeStats::recursiveUpdate(Bone *b)
{
    // TREESHAPE BONES LENGTH
    length = b->getLength();

    // TREESHAPE WEIGHT
    weight = 1.0/b->getRigidBody()->getInvMass(); // (compound bone + fix)

    if(computeBonesWeight)
        treeshapeWeight->setValue(weight);
    if(computeBonesLength)
        treeshapeBonesLength->setValue(length);
    if(computeBonesNb)
        treeshapeBones->setValue(b->getEndFixation()->getBones().size());
    if(computeEffectorsNb) {
        treeshapeNbEffectors->setValue(1);
        treeshapeNbEffectors->setValue(b->getEndFixation()->getEffectors().size());
    }
    if(computeSensorsNb) {
        treeshapeNbSensors->setValue(b->getEndFixation()->getSensors().size());
    }

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

    if(computeBonesWeight) {
        treeshapeWeight->setValue(weight);
    }

    if(computeBonesNb) {
        treeshapeBones->setValue(treeshape->getRoot()->getBones().size());
    }

    if(computeEffectorsNb) {
        treeshapeNbEffectors->setValue(treeshape->getRoot()->getEffectors().size());
    }

    if(computeSensorsNb) {
        treeshapeNbSensors->setValue(treeshape->getRoot()->getSensors().size());
    }

    // TREESHAPE VERTICAL HEIGHT
    // Algo : find the heighter and the lower fixation in y axis, height = max - min
    minHeightY = maxHeightY = treeshape->getRoot()->getRigidBody()->getWorldTransform().getOrigin().y();

    foreach (Bone *b, treeshape->getRoot()->getBones())
        recursiveUpdate(b);

    treeshapeVerticalHeight->setValue(maxHeightY - minHeightY);

    /*if(computeBonesLength) {
        treeshapeBonesLength->setValue(0);
    }
    if(computeBonesNb) {
        treeshapeBones->setValue(0);
    }
    if(computeBonesWeight) {
        treeshapeWeight->setValue(0);
    }
    if(computeEffectorsNb) {
        treeshapeNbEffectors->setValue(0);
    }
    if(computeSensorsNb) {
        treeshapeNbSensors->setValue(0);
    }*/

    computeBonesLength = false;
    computeBonesNb = false;
    computeBonesWeight = false;
    computeEffectorsNb = false;
    computeSensorsNb = false;
}


void TreeShapeStats::reset() {
    if(treeshapeBones->getSum() == 0)
        computeBonesNb = true;
    if(treeshapeBonesLength->getSum() == 0)
        computeBonesLength = true;
    if(treeshapeWeight->getSum() == 0)
        computeBonesWeight = true;
    if(treeshapeNbSensors->getSum() == 0)
        computeSensorsNb = true;
    if(treeshapeNbEffectors->getSum() == 0)
        computeEffectorsNb = true;
}


}
