#ifndef MUTATIONSMANAGER_H
#define MUTATIONSMANAGER_H

#include <QVariant>
#include <body/bone.h>

namespace GeneLabCore {

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

private:

    // To mutate a value in a map
    void mutate(QVariantMap &map, QString key, float probOfMutation, float minFactor, float maxFactor, float minValue, float maxValue);

    QVariant recursiveMutateTreeShape(QVariant &boneVariant);

    // BONE

    // Bone Length mutation
    float probOfBoneLengthMutation;     // probability of length mutation
    float minFactOfBoneLengthMutation;  // factor of min length mutation
    float maxFactOfBoneLengthMutation;  // factor of max length mutation
    float minBoneLength;                // min bone length in meter
    float maxBoneLength;                // max bone length in meter

    // Bone radius mutation
    float probOfBoneRadiusMutation;     // probability of radius mutation
    float minFactOfBoneRadiusMutation;  // factor of min radius mutation
    float maxFactOfBoneRadiusMutation;  // factor of max radius mutation
    float minBoneRadius;                // min bone radius in meter
    float maxBoneRadius;                // max bone radius in meter


    // FIXATION

    // Fixation radius mutation
    float probOfFixRadiusMutation;      // probability of radius mutation
    float minFactOfFixRadiusMutation;   // factor of min radius mutation
    float maxFactOfFixRadiusMutation;   // factor of max radius mutation
    float minFixRadius;                 // min fix radius in meter
    float maxFixRadius;                 // max fix radius in meter

};

}

#endif // MUTATIONSMANAGER_H
