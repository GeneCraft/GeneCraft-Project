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

#include <QJsonObject>
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
    MutationsManager(QJsonObject mutationsParams);
    ~MutationsManager();
    QJsonObject serialize();

    // To mutate an entire entity
    QJsonObject mutateEntity(const QJsonObject &entityVariant);

    // To mutate a treeshape
    QJsonObject mutateTreeShape(const QJsonObject &treeShapeVariant);

    // To mutate a fixation (Not recursively)
    QJsonObject mutateBone(const QJsonObject &boneVariant);

    // To mutate a fixation (Not recursively)
    QJsonObject mutateFixation(const QJsonObject &fixVariant);

    // Mutate the brain
    QJsonObject mutateBrain(QJsonObject brain);

    // Mutate a brainInput
    QJsonObject mutateBrainIn(QJsonObject brainIn);

    // Mutate a brainOutput
    QJsonObject mutateBrainOut(QJsonObject brainOut);

    // Mutate the tree of a brainOutput
    QJsonObject mutateBrainOutTree(QJsonObject brainOut);

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
    void mutate(QJsonObject &map, QString key, Mutation* mutation);
    int treeDepth(QStringList::iterator& it);
    void consumnSubTree(QStringList::iterator& it);

    /**
     * To add sensor
     *
     * @param the QJsonArray where add
     * @param the position to add (-1 = end of list)
     */
    void addSensor(QJsonArray &sensors, int i=-1);

    /**
     * To add effector
     *
     * @param the QJsonArray where add
     * @param the position to add (-1 = end of list)
     */
    void addEffector(QJsonArray &effectorsList, int i=-1);

    /**
     * To add bone
     *
     * @param the QJsonArray where add
     * @param the position to add (-1 = end of list)
     */
    void addBone(QJsonArray &bones, int i=-1, QJsonObject endFix = QJsonObject());


    QJsonObject recursiveMutateTreeShape(QJsonObject &boneVariant);

};

}

#endif // MUTATIONSMANAGER_H
