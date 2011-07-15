#ifndef MUTATIONSMANAGER_H
#define MUTATIONSMANAGER_H

#include <QVariant>
#include <QStringList>
#include <QMap>
#include "body/bone.h"
#include "mutation.h"
#include "bonelimitsmutation.h"
#include "genelabcoreclasses.h"

namespace GeneLabCore {

class MutationsManager
{
public:

    // To create the mutation manager
    MutationsManager();
    MutationsManager(QVariant mutationsParams);
    QVariant serialize();

    // To mutate an entire entity
    QVariant mutateEntity(const QVariant &entityVariant);

    // To mutate a treeshape
    QVariant mutateTreeShape(const QVariant &treeShapeVariant);

    // To mutate a fixation (Not recursively)
    QVariant mutateBone(const QVariant &boneVariant);

    // To mutate a fixation (Not recursively)
    QVariant mutateFixation(const QVariant &fixVariant);

    // Mutate the brain
    QVariant mutateBrain(QVariant brain);

    // Mutate a brainInput
    QVariant mutateBrainIn(QVariant brainIn);

    // Mutate a brainOutput
    QVariant mutateBrainOut(QVariant brainOut);

    // Mutate the tree of a brainOutput
    QVariant mutateBrainOutTree(QVariant brainOut);

    // BODY

    // Bone Length mutation
    FloatMutation* boneLength;

    // Bone radius mutation
    FloatMutation* boneRadius;

    // Bone angular origin (Yaw and Roll)
    FloatMutation* boneAngularOrigin;

    // Bone angular limits (x,y,z for lower and upper)
    BoneLimitsMutation* boneAngularLimits;

    // Fixation radius mutation
    FloatMutation* fixRadius;

    // New sensor
    StructuralMutation *sensorsMutation;
    StructuralList *sensorStructuralList;

    // BRAIN

    // Brain size
    IntegerMutation* brainSize;

    // Input positions
    FloatMutation* brainInPos;

    // Input weight
    FloatMutation* brainWeight;

    // Constant value
    FloatMutation *constValue;

    // Brain memory size
    IntegerMutation* brainMemorySize;

    // Brain frequency
    IntegerMutation* brainFrequency;

    // New brain tree luck
    SimpleProbabilityMutation* newBrainTree;

private:

    // To mutate a value in a map
    void mutate(QVariantMap &map, QString key, Mutation* mutation);
    int treeDepth(QStringListIterator it);
    void consumnSubTree(QStringListIterator it);

    QVariant recursiveMutateTreeShape(QVariant &boneVariant);

};

}

#endif // MUTATIONSMANAGER_H
