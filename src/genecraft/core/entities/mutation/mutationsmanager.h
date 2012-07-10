/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MUTATIONSMANAGER_H
#define MUTATIONSMANAGER_H

#include <QVariant>
#include <QStringList>
#include <QMap>
#include "body/bone.h"
#include "mutation.h"
#include "bonelimitsmutation.h"
#include "genecraftcoreclasses.h"

namespace GeneCraftCore {

class MutationsManager
{
public:

    // To create the mutation manager
    MutationsManager();    
    MutationsManager(QVariant mutationsParams);
    ~MutationsManager();
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

    // Mutate the realSpider parameters
    QVariant mutateParams(const QVariant &params);

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
    StructuralList *sensorsStructuralList;

    // Add / Remove / Replace bone
    StructuralMutation *bonesStructural;

    // Add / Remove / Replace effector
    StructuralMutation *effectorsStructural;
    StructuralList *effectorsStructuralList;

    // ------------
    // -- params --
    // ------------

    // Leg Length mutation
    FloatMutation* legLength;

    // Leg Radius mutation
    FloatMutation* legRadius;

    // Body Radius mutation
    FloatMutation* bodyRadius;

    // Knee Radius mutation
    FloatMutation* kneeRadius;

    // -----------
    // -- brain --
    // -----------

    // Input positions
    FloatMutation* brainInPos;

    // Input weight
    FloatMutation* brainWeight;

    // Input distance
    FloatMutation* brainDistance;

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
     * To add effector
     *
     * @param the QVariantList where add
     * @param the position to add (-1 = end of list)
     */
    void addEffector(QVariantList &effectorsList, int i=-1);

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
