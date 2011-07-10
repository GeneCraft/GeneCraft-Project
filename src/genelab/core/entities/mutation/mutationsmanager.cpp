#include "mutationsmanager.h"

#include <QVariantMap>
#include <QVariantList>
#include "tools.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include "floatmutation.h"
#include "integermutation.h"
#include "brainnodemutation.h"
#include "sensors/sensor.h"
#include "brain/brainnode.h"

#define MAX_MUTATION_TRIES 100

namespace GeneLabCore {

    MutationsManager::MutationsManager(QVariant mutationsParams)
    {
        // Bone Length
        boneLength = new FloatMutation();
        boneLength->probability  = 0.;
        boneLength->minFact      = -0.5;
        boneLength->maxFact      =  0.5;
        boneLength->minValue     = 0.1;
        boneLength->maxValue     = 5.0;

        // Bone radius mutation
        boneRadius = new FloatMutation();
        boneRadius->probability  = 0.;
        boneRadius->minFact      = -0.5;
        boneRadius->maxFact      =  0.5;
        boneRadius->minValue     = 0.1;
        boneRadius->maxValue     = 2.0;

        // Fixation radius mutation
        fixRadius = new FloatMutation();
        fixRadius->probability   = 0.;
        fixRadius->minFact       = -0.5;
        fixRadius->maxFact       =  0.5;
        fixRadius->minValue      = 0.1;
        fixRadius->maxValue      = 2.0;

        // Plug grid size
        brainSize = new IntegerMutation();
        brainSize->probability   = 1.;
        brainSize->minIncr       = -3;
        brainSize->maxIncr       =  3;
        brainSize->minValue      = 1;
        brainSize->maxValue      = 100;

        // Position X of Input
        brainInPos = new FloatMutation();
        brainInPos->probability = 1;
        brainInPos->minFact     = -0.1;
        brainInPos->maxFact     =  0.1;
        brainInPos->minValue    = 0;
        brainInPos->maxValue    = 1;

        // BrainWeight
        brainWeight = new FloatMutation();
        brainWeight->probability = 1;
        brainWeight->minFact    = -0.1;
        brainWeight->maxFact    =  0.1;
        brainWeight->minValue   = -1.0;
        brainWeight->maxValue   =  1.0;

        // Brain memory size
        brainMemorySize = new IntegerMutation();
        brainMemorySize->probability    = 1;
        brainMemorySize->minIncr        = -3;
        brainMemorySize->maxIncr        =  3;
        brainMemorySize->minValue       = 1;
        brainMemorySize->maxValue       = 100;

    }


    QVariant MutationsManager::mutateEntity(const QVariant &entityVariant) {
        QVariantMap entityMap = entityVariant.toMap();
        QVariantMap bodyMap = entityMap["body"].toMap();
        QVariantMap treeShapeMap = bodyMap["shape"].toMap();
        QVariantMap brainMap = entityMap["brain"].toMap();

        QVariant newTreeShapeMap = this->mutateTreeShape(treeShapeMap);
        QVariant newBrainMap     = this->mutateBrain(brainMap);

        bodyMap.insert("shape",   newTreeShapeMap);
        entityMap.insert("body",  bodyMap);
        entityMap.insert("brain", newBrainMap);

        return entityMap;

    }


    QVariant MutationsManager::mutateTreeShape(const QVariant &treeShapeVariant)
    {
        // Convert to map  (IT'S NOW A COPY !)
        QVariantMap treeShapeMap = treeShapeVariant.toMap();

        // mutate the root fix
        QVariant rootFixVariant = treeShapeMap.value("rootFix");
        rootFixVariant = mutateFixation(rootFixVariant);

        // mutate all bones
        QVariantMap rootFixMap = rootFixVariant.toMap(); // COPY !
        QVariantList newBonesList;
        foreach(QVariant boneVariant, rootFixMap.value("bones").toList())
            newBonesList.append(recursiveMutateTreeShape(boneVariant));

        rootFixMap.insert("bones",newBonesList);
        treeShapeMap.insert("rootFix",rootFixMap);
        return treeShapeMap;
    }

    QVariant MutationsManager::recursiveMutateTreeShape(QVariant &boneVariant) {

        // mutate bone
        boneVariant = mutateBone(boneVariant);
        QVariantMap boneVariantMap = boneVariant.toMap(); // COPY !

        // mutate the end fix
        QVariant endFixVariant = boneVariantMap.value("endFix"); // COPY !
        endFixVariant = mutateFixation(endFixVariant);

        // mutate all bones
        QVariantMap endFixMap = endFixVariant.toMap(); // COPY !
        QVariantList newBonesList;
        foreach(QVariant boneVariant, endFixMap.value("bones").toList())
            newBonesList.append(recursiveMutateTreeShape(boneVariant));

        endFixMap.insert("bones",newBonesList);
        boneVariantMap.insert("endFix",endFixMap);

        return boneVariantMap;
    }

    QVariant MutationsManager::mutateBone(const QVariant &boneVariant){

        QVariantMap boneMap = boneVariant.toMap();

        // length mutation
        boneLength->mutate(boneMap, "length");

        // radius mutation
        boneRadius->mutate(boneMap, "radius");

        // ----------------------
        // -- motors mutations --
        // ----------------------
        QVariantMap newMuscle;
        QVariantMap newOuts;
        QVariantMap outs = boneMap["muscle"].toMap()["outs"].toMap();

        // foreach motor axis...
        for(int i=0; i<3; ++i){

            // get motor name
            QString motor;
            if(i == 0) motor = "x";
            else if(i == 1) motor = "y";
            else motor = "z";

            // if motor exists
            if(outs.contains(motor))
            {
                QVariantMap newOut;
                QVariantMap out = outs[motor].toMap();
                QVariantList newBrainOuts;
                QVariantList brainOuts = out["brainOuts"].toList();

                foreach(QVariant brainOut, brainOuts){
                    // add new brainOut
                    newBrainOuts.append(mutateBrainOut(brainOut));
                }

                newOut.insert("brainOuts",newBrainOuts);
                newOuts.insert(motor,newOut);
            }
        }

        newMuscle.insert("type",QVariant("RotationalMotor"));
        newMuscle.insert("outs",newOuts);
        boneMap.insert("muscle",newMuscle);

        return boneMap;
    }

    QVariant MutationsManager::mutateFixation(const QVariant &fixVariant){

        QVariantMap fixMap = fixVariant.toMap();

        // radius mutation
        fixRadius->mutate(fixMap, "radius");

        // Sensors mutations
        QVariantList sensorList = fixMap["sensors"].toList();
        QVariantList newSensorList;
        foreach(QVariant sensor, sensorList) {
            QVariantMap sensorMap = sensor.toMap();
            SensorType type = (SensorType)sensorMap["type"].toInt();
            switch(type) {
                case accelerometer:
                    sensorMap.insert("inputX", mutateBrainIn(sensorMap["inputX"]));
                    sensorMap.insert("inputY", mutateBrainIn(sensorMap["inputY"]));
                    sensorMap.insert("inputZ", mutateBrainIn(sensorMap["inputZ"]));
                    break;
                case gyroscopic:
                    sensorMap.insert("inputPitch", mutateBrainIn(sensorMap["inputPitch"]));
                    sensorMap.insert("inputYaw",   mutateBrainIn(sensorMap["inputYaw"]));
                    sensorMap.insert("inputRoll",  mutateBrainIn(sensorMap["inputRoll"]));
                    break;
                case position:
                    sensorMap.insert("inputX", mutateBrainIn(sensorMap["inputX"]));
                    sensorMap.insert("inputY", mutateBrainIn(sensorMap["inputY"]));
                    sensorMap.insert("inputZ", mutateBrainIn(sensorMap["inputZ"]));
                    break;
                case contact:
                    sensorMap.insert("collisionInput", mutateBrainIn(sensorMap["collisionInput"]));
                    break;
            }

            newSensorList.append(sensorMap);
        }

        fixMap.insert("sensors", newSensorList);

        return fixMap;
    }

    // Mutate the brain
    QVariant MutationsManager::mutateBrain(QVariant brain) {
        QVariantMap brainMap = brain.toMap();
        brainSize->mutate(brainMap, "plugGridSize");
        return brainMap;
    }

    // Mutate a brainInput
    QVariant MutationsManager::mutateBrainIn(QVariant brainIn) {
        // "inputRoll":{"connexions":[{"w":-0.0762658,"x":0.471847,"y":0.920957}
        QVariantMap inMap = brainIn.toMap();
        QVariantList connexions = inMap["connexions"].toList();
        QVariantList newConnexions;

        foreach(QVariant connexion, connexions) {
            // To map !
            QVariantMap connexionMap = connexion.toMap();

            // mutation of position
            brainInPos->mutate(connexionMap, "x");
            brainInPos->mutate(connexionMap, "y");

            // mutation of weight
            brainWeight->mutate(connexionMap, "w");
            newConnexions.append(connexionMap);
        }

        inMap.insert("connexions", newConnexions);

        return inMap;
    }

    // Mutate a brainOutput
    QVariant MutationsManager::mutateBrainOut(QVariant brainOut) {
        QVariantMap outMap = brainOut.toMap();

        QString treeData = outMap["connexionInfo"].toString();
        QStringList nodes = treeData.split(",", QString::SkipEmptyParts);

        QString newConnexionInfo;
        foreach(QString node, nodes) {
            QStringList nodePart = node.split(" ", QString::SkipEmptyParts);
            NodeType t = fromString(nodePart[0]);
            switch(t) {
            // 2 operands
            case SUM:
            case PRODUCT:
            case DIVIDE:
            case ATAN:
            // 2 operands + decisions
            case THRESOLD: // --------> THRESHOLD ;)
            case GT:
            // 3 operands
            case IFELSE:

            // 1 operand
            case COS:
            case SIN:
            case ABS:
            case SIGN_OF:
            case LOG:
            case EXP:
            case SIGM:
                // No mutation for thoses !
                newConnexionInfo.append(node);
                newConnexionInfo.append(",");
                break;
            case IN:
                // x et y
                newConnexionInfo.append(nodePart[0]);
                newConnexionInfo.append(" " +
                            QString::number(brainInPos->mutate(nodePart[1].toFloat())));
                newConnexionInfo.append(" " +
                            QString::number(brainInPos->mutate(nodePart[2].toFloat())));
                newConnexionInfo.append(",");
                break;
            case CONST:
                newConnexionInfo.append(nodePart[0]);
                newConnexionInfo.append(" " +
                            QString::number(brainWeight->mutate(nodePart[1].toFloat())));
                newConnexionInfo.append(",");
                break;
            case INTEGRATE:
            case INTERPOLATE:
            case DIFFERENTIATE:
            case MEMORY:
            case SMOOTH:
            case MIN:
            case MAX:
                newConnexionInfo.append(nodePart[0]);
                newConnexionInfo.append(" " +
                            QString::number(brainMemorySize->mutate(nodePart[1].toInt())));
                newConnexionInfo.append(",");
                break;
            case SINUS:
                newConnexionInfo.append(node);
                newConnexionInfo.append(",");
                break;
            case MEMORY_SPACE:
            case BAD_TYPE:
                qDebug() << "SHOULD NOT BE IN STRING memoryspace or badtype !!";
                break;

            }
        }

        outMap.insert("connexionInfo", newConnexionInfo);

        return outMap;
    }
}
