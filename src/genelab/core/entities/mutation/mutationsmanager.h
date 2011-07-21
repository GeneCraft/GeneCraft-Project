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

    // ----------
    // -- body --
    // ----------

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

    // Add / Remove / Replace sensor
    StructuralMutation *sensorsStructural;
    StructuralList *sensorStructuralList;

    // Add / Remove / Replace sensor
    StructuralMutation *bonesStructural;

    // -----------
    // -- brain --
    // -----------

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
    StructuralMutation* brainStructural;
    StructuralList*     brainNodeList;

    // Sensors params
    FloatMutation *distanceSensorYZ;

private:

    // To mutate a value in a map
    void mutate(QVariantMap &map, QString key, Mutation* mutation);
    int treeDepth(QStringList::iterator& it);
    void consumnSubTree(QStringList::iterator& it);

    /**
     * To add sensor
     *
     * @param the QVariantList where add
     * @param the position to add (-1 = end of list)
     */
    void addSensor(QVariantList &sensors, int i=-1);

    /**
     * To add bone
     *
     * @param the QVariantList where add
     * @param the position to add (-1 = end of list)
     */
    void addBone(QVariantList &bones, int i=-1, QVariant endFix = QVariant());

    QVariant recursiveMutateTreeShape(QVariant &boneVariant);

};

}

#endif // MUTATIONSMANAGER_H
