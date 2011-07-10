#ifndef MUTATIONSMANAGER_H
#define MUTATIONSMANAGER_H

#include <QVariant>
#include <body/bone.h>

namespace GeneLabCore {

    struct Mutation {
        float probability;
        float minFact;
        float maxFact;
        float minValue;
        float maxValue;
    };

class MutationsManager
{
public:

    // To create the mutation manager
    MutationsManager(QVariant mutationsParams);

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
    void mutate(QVariantMap &map, QString key, Mutation mutation);

    QVariant recursiveMutateTreeShape(QVariant &boneVariant);

    // BONE

    // Bone Length mutation
    Mutation boneLength;                // max bone length in meter

    // Bone radius mutation
    Mutation boneRadius;                // max bone radius in meter


    // FIXATION

    // Fixation radius mutation
    Mutation fixRadius;                 // max fix radius in meter

    Mutation brainSize;
    Mutation brainInPosX;
    Mutation brainInPosY;

};

}

#endif // MUTATIONSMANAGER_H
