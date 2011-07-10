#ifndef MUTATIONSMANAGER_H
#define MUTATIONSMANAGER_H

#include <QVariant>
#include <body/bone.h>
#include "mutation.h"
#include "floatmutation.h"
#include "integermutation.h"

namespace GeneLabCore {

class MutationsManager
{
public:

    // To create the mutation manager
    MutationsManager(QVariant mutationsParams);

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

private:

    // To mutate a value in a map
    void mutate(QVariantMap &map, QString key, Mutation* mutation);

    QVariant recursiveMutateTreeShape(QVariant &boneVariant);

    // BONE

    // Bone Length mutation
    FloatMutation* boneLength;                // max bone length in meter

    // Bone radius mutation
    FloatMutation* boneRadius;                // max bone radius in meter


    // FIXATION

    // Fixation radius mutation
    FloatMutation* fixRadius;                 // max fix radius in meter

    // BRAIN

    // Brain size
    IntegerMutation* brainSize;

    // Input positions
    FloatMutation* brainInPos;

    // Input weight
    FloatMutation* brainWeight;

};

}

#endif // MUTATIONSMANAGER_H
