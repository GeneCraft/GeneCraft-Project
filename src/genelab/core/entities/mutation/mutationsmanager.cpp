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
#include "brain/brainfunctional.h"
#include "simpleprobabilitymutation.h"
#include "structuralmutation.h"
#include "structurallist.h"

// Sensors
#include "sensors/accelerometersensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/positionsensor.h"
#include "sensors/contactsensor.h"

#include "qxtjson.h"

namespace GeneLabCore {

    MutationsManager::MutationsManager()
    {
        // --------------------
        // -- BODY MUTATIONS --
        // --------------------

        // Bone Length
        boneLength = new FloatMutation();
        boneLength->probability  = 0.1;
        boneLength->minFact      = -0.05;
        boneLength->maxFact      =  0.05;
        boneLength->minValue     = 0.1;
        boneLength->maxValue     = 5.0;

        // Bone radius mutation
        boneRadius = new FloatMutation();
        boneRadius->probability  = 0.1;
        boneRadius->minFact      = -0.05;
        boneRadius->maxFact      =  0.05;
        boneRadius->minValue     = 0.1;
        boneRadius->maxValue     = 2.0;

        // Fixation radius mutation
        fixRadius = new FloatMutation();
        fixRadius->probability   = 0.1;
        fixRadius->minFact       = -0.05;
        fixRadius->maxFact       =  0.05;
        fixRadius->minValue      = 0.1;
        fixRadius->maxValue      = 2.0;

        // Bone angular origin (Yaw and Roll)
        boneAngularOrigin = new FloatMutation();
        boneAngularOrigin->probability   = 0.1;
        boneAngularOrigin->minFact       = -0.01;
        boneAngularOrigin->maxFact       =  0.01;
        boneAngularOrigin->minValue      = -M_PI+0.01; // -INF (cyclic) ?
        boneAngularOrigin->maxValue      =  M_PI-0.01; // +INF (cyclic) ?

        // Bone angular limits (x,y,z for lower and upper)
        boneAngularLimits = new BoneLimitsMutation();

        // sensors
        sensorsStructural = new StructuralMutation();
        sensorsStructural->addProbability = 0.1f;
        sensorsStructural->deleteProbability = 0.1f;
        sensorsStructural->replaceProbability = 0.1f;
        sensorStructuralList = new StructuralList();
        sensorStructuralList->elements.append(new MutationElement("Accelerometer sensor",accelerometerSensor,1.0));
        sensorStructuralList->elements.append(new MutationElement("Gyroscopic sensor",gyroscopicSensor,1.0));
        sensorStructuralList->elements.append(new MutationElement("Egocentric sensor",positionSensor,1.0));
        sensorStructuralList->elements.append(new MutationElement("Contact sensor",contactSensor,1.0));

        // bones
        bonesStructural = new StructuralMutation();
        bonesStructural->addProbability = 0.01f;
        bonesStructural->deleteProbability = 0.01f;
        bonesStructural->replaceProbability = 0.01f;

        // ---------------------
        // -- BRAIN MUTATIONS --
        // ---------------------

        // Plug grid size
        brainSize = new IntegerMutation();
        brainSize->probability   = 0.1;
        brainSize->minIncr       = -5;
        brainSize->maxIncr       =  5;
        brainSize->minValue      = 1;
        brainSize->maxValue      = 100;

        // Position X of Input
        brainInPos = new FloatMutation();
        brainInPos->probability = 0.2;
        brainInPos->minFact     = -0.1;
        brainInPos->maxFact     =  0.1;
        brainInPos->minValue    = 0;
        brainInPos->maxValue    = 1;

        // BrainWeight
        brainWeight = new FloatMutation();
        brainWeight->probability = 0.2;
        brainWeight->minFact    = -0.1;
        brainWeight->maxFact    =  0.1;
        brainWeight->minValue   = -1.0;
        brainWeight->maxValue   =  1.0;

        // Brain memory size
        brainMemorySize = new IntegerMutation();
        brainMemorySize->probability    = 0.2;
        brainMemorySize->minIncr        = -5;
        brainMemorySize->maxIncr        =  5;
        brainMemorySize->minValue       = 1;
        brainMemorySize->maxValue       = 100;

        // Brain frequency
        brainFrequency = new IntegerMutation();
        brainFrequency->probability     = 0.1;
        brainFrequency->minIncr      = -2;
        brainFrequency->maxIncr      =  2;
        brainFrequency->minValue     =  1;
        brainFrequency->maxValue     = 60;

        // New brain tree probability
        newBrainTree = new SimpleProbabilityMutation();

        // Brain constant value
        constValue = new FloatMutation();
        constValue->probability = 0.2;
        constValue->minFact = -0.1;
        constValue->maxFact = 0.1;
        constValue->minValue = -10;
        constValue->maxValue = 10;
    }

    MutationsManager::MutationsManager(QVariant mutationsParams)
    {
        QVariantMap map = mutationsParams.toMap();

        // --------------------
        // -- BODY MUTATIONS --
        // --------------------
        boneLength = new FloatMutation(map["boneLength"]);
        boneRadius = new FloatMutation(map["boneRadius"]);
        fixRadius = new FloatMutation(map["fixRadius"]);
        boneAngularOrigin = new FloatMutation(map["boneAngularOrigin"]);

        // TODO !!!
        // Bone angular limits (x,y,z for lower and upper)
        boneAngularLimits = new BoneLimitsMutation();
        boneAngularLimits->probability                  = 0.1;
        boneAngularLimits->axisMutation->probability    = 0.1;
        boneAngularLimits->axisMutation->minFact        = -0.01;
        boneAngularLimits->axisMutation->maxFact        =  0.01;
        boneAngularLimits->axisMutation->minValue       = -M_PI+0.01; // -INF (cyclic) ?
        boneAngularLimits->axisMutation->maxValue       =  M_PI-0.01; // +INF (cyclic) ?

        // sensors
        sensorsStructural = new StructuralMutation(map["sensorsStructural"]);
        sensorStructuralList = new StructuralList(map["sensorStructuralList"]);

        // bones
        bonesStructural = new StructuralMutation(map["bonesStructural"]);

        // ---------------------
        // -- BRAIN MUTATIONS --
        // ---------------------

        // Plug grid size
        brainSize = new IntegerMutation(map["brainSize"]);
        brainInPos = new FloatMutation(map["brainInPos"]);
        brainWeight = new FloatMutation(map["brainWeight"]);
        brainMemorySize = new IntegerMutation(map["brainMemorySize"]);
        brainFrequency = new IntegerMutation(map["brainFrequency"]);
        newBrainTree = new SimpleProbabilityMutation(map["newBrainTree"]);
        constValue = new FloatMutation(map["constValue"]);
    }

    QVariant MutationsManager::serialize(){

        QVariantMap map;

        map.insert("boneLength",boneLength->serialize());
        map.insert("boneRadius",boneRadius->serialize());
        map.insert("fixRadius",fixRadius->serialize());
        map.insert("boneAngularOrigin",boneAngularOrigin->serialize());
        map.insert("brainSize",brainSize->serialize());
        map.insert("brainInPos",brainInPos->serialize());
        map.insert("brainWeight",brainWeight->serialize());
        map.insert("brainMemorySize",brainMemorySize->serialize());
        map.insert("brainFrequency",brainFrequency->serialize());
        map.insert("newBrainTree",newBrainTree->serialize());
        map.insert("constValue",constValue->serialize());

        map.insert("sensorsStructural",sensorsStructural->serialize());
        map.insert("sensorStructuralList",sensorStructuralList->serialize());

        map.insert("bonesStructural",bonesStructural->serialize());

        return map;
    }

    QVariant MutationsManager::mutateEntity(const QVariant &entityVariant) {
        QVariantMap entityMap = entityVariant.toMap();
        QVariantMap originsMap =  entityMap["origins"].toMap();
        QVariantMap bodyMap = entityMap["body"].toMap();
        QVariantMap treeShapeMap = bodyMap["shape"].toMap();
        QVariantMap brainMap = entityMap["brain"].toMap();
        int generation = entityMap["generation"].toInt();
        entityMap.insert("generation", generation+1);

        // treeshape mutation
        QVariant newTreeShapeMap = this->mutateTreeShape(treeShapeMap);
        bodyMap.insert("shape",   newTreeShapeMap);
        entityMap.insert("body",  bodyMap);

        // brain mutation
        QVariant newBrainMap     = this->mutateBrain(brainMap);
        entityMap.insert("brain", newBrainMap);

        // next generation
        originsMap.insert("generation", originsMap["generation"].toInt()+1);
        entityMap.insert("origins", originsMap);

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

        // add new bone to fix
        if(bonesStructural->checkAdd())
            addBone(newBonesList);

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

        // add new bone to fix
        if(bonesStructural->checkAdd())
             addBone(newBonesList);

        endFixMap.insert("bones",newBonesList);
        boneVariantMap.insert("endFix",endFixMap);

        return boneVariantMap;
    }

    QVariant MutationsManager::mutateBone(const QVariant &boneVariant){

        QVariantMap boneMap = boneVariant.toMap();

        // ----------
        // -- size --
        // ----------

        //qDebug() << boneLength->enable << boneLength->probability;

        // length mutation
        boneLength->mutate(boneMap, "length");

        // radius mutation
        boneRadius->mutate(boneMap, "radius");

        // --------------------
        // -- angular origin --
        // --------------------
        QVariantMap localRotation = boneMap["localRotation"].toMap();
        boneAngularOrigin->mutate(localRotation,"y");
        boneAngularOrigin->mutate(localRotation,"z");
        boneMap.insert("localRotation",localRotation);

        // --------------------
        // -- angular limits --
        // --------------------

        QVariantMap lowerLimits = boneMap["lowerLimits"].toMap();
        QVariantMap upperLimits = boneMap["upperLimits"].toMap();

        boneAngularLimits->mutate(lowerLimits,upperLimits);

        boneMap.insert("lowerLimits",lowerLimits);
        boneMap.insert("upperLimits",upperLimits);


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

        // -----------------------
        // -- Sensors mutations --
        // -----------------------
        QVariantList sensorList = fixMap["sensors"].toList();
        QVariantList newSensorList;

        int nbSensors = sensorList.count();
        for(int i=0;i<nbSensors;++i) {

           // delete sensor
           if(sensorsStructural->checkDelete()) {
                sensorList.removeAt(i);
                i--;
                nbSensors--;
           }
           // replace sensor
           else if(sensorsStructural->checkReplace()) {
               sensorList.removeAt(i);
               addSensor(sensorList,i);
           }
        }

        // mutate sensor brain in
        foreach(QVariant sensor, sensorList) {
            QVariantMap sensorMap = sensor.toMap();
            SensorType type = (SensorType)sensorMap["type"].toInt();
            switch(type) {
                case accelerometerSensor:
                    sensorMap.insert("inputX", mutateBrainIn(sensorMap["inputX"]));
                    sensorMap.insert("inputY", mutateBrainIn(sensorMap["inputY"]));
                    sensorMap.insert("inputZ", mutateBrainIn(sensorMap["inputZ"]));
                    break;
                case gyroscopicSensor:
                    sensorMap.insert("inputPitch", mutateBrainIn(sensorMap["inputPitch"]));
                    sensorMap.insert("inputYaw",   mutateBrainIn(sensorMap["inputYaw"]));
                    sensorMap.insert("inputRoll",  mutateBrainIn(sensorMap["inputRoll"]));
                    break;
                case positionSensor:
                    sensorMap.insert("inputX", mutateBrainIn(sensorMap["inputX"]));
                    sensorMap.insert("inputY", mutateBrainIn(sensorMap["inputY"]));
                    sensorMap.insert("inputZ", mutateBrainIn(sensorMap["inputZ"]));
                    break;
                case contactSensor:
                    sensorMap.insert("collisionInput", mutateBrainIn(sensorMap["collisionInput"]));
                    break;
            }

            newSensorList.append(sensorMap);
        }

        // add sensor ?
        if(sensorsStructural->checkAdd())
            addSensor(newSensorList);

        fixMap.insert("sensors", newSensorList);

        // ---------------------
        // -- Bones mutations --
        // ---------------------
        QVariantList bonesList = fixMap["bones"].toList();

        for(int i=0;i<bonesList.count();++i) {
           // Delete
           if(bonesStructural->checkDelete()) {
                QVariantMap boneMap = bonesList.takeAt(i).toMap();
                QVariantMap fixMap = boneMap["endFix"].toMap();
                QVariantList bones = fixMap["bones"].toList();
                int nbBones;
                bonesList.append(bones);
                i--;
                nbBones = bonesList.count();
           }
           // Insert
           else if(bonesStructural->checkAdd()) {
               // Un copie de l'os précédent est plus intéressante qu'un os totalement random
               // The new bone
               QVariant oldBone = bonesList.takeAt(i);
               QVariantMap newBoneMap = oldBone.toMap();
               this->boneLength->mutate(newBoneMap, "length");
               this->boneRadius->mutate(newBoneMap, "radius");

               // And his fixation
               QVariantMap newEndFixation = newBoneMap["endFix"].toMap();
               this->fixRadius->mutate(newEndFixation, "radius");

               // The son
               QVariantList newBones;
               newBones.append(oldBone);
               newEndFixation.insert("bones", newBones);
               newBoneMap.insert("endFix", newEndFixation);

               // Adding the child to the parent
               bonesList.insert(i, newBoneMap);

           }
           // Replace
           else if(bonesStructural->checkReplace()) {
               QVariantMap boneMap = bonesList.takeAt(i).toMap();
               QVariant endFix = boneMap["endFix"];
               addBone(bonesList,i, endFix); // Took the old endFix back
           }
        }

        // --
        // (?) adding of bone : after bone mutation to avoid recurcive calls
        // (you add a bone then the end fix of this bone will be also mutated...)
        // see : recursiveMutateTreeShape(...)
        // --

        fixMap.insert("bones", bonesList);

        return fixMap;
    }

    void MutationsManager::addBone(QVariantList &bonesList, int i, QVariant endFix) {
        QVariantMap newBone = Bone::generateEmpty().toMap();

        if(endFix != QVariant())
            newBone.insert("endFix", endFix);

        // insert in a specific position
        if(i > -1 && i < bonesList.count())
            bonesList.insert(i,newBone);
        else
            bonesList.append(newBone);
    }

    // add sensor
    void MutationsManager::addSensor(QVariantList &sensorsList, int i) {

        MutationElement *me = sensorStructuralList->pickOne();
        QVariant newSensor;

        switch(me->type) {
            case accelerometerSensor:
                newSensor = AccelerometerSensor::generateEmpty();
                break;
            case gyroscopicSensor:
                newSensor = GyroscopicSensor::generateEmpty();
                break;
            case positionSensor:
                newSensor = PositionSensor::generateEmpty();
                break;
            case contactSensor:
                newSensor = ContactSensor::generateEmpty();
                break;
        }

        // insert in a specific position
        if(i > -1 && i < sensorsList.count())
            sensorsList.insert(i,newSensor);
        else
            sensorsList.append(newSensor);
    }

    // Mutate the brain
    QVariant MutationsManager::mutateBrain(QVariant brain) {
        QVariantMap brainMap = brain.toMap();
        brainSize->mutate(brainMap, "plugGridSize");
        brainFrequency->mutate(brainMap, "frequency");
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

        // Small change of replacing to entire brain tree

        QString newConnexionInfo;

        if(newBrainTree->canMutate()) {
            newConnexionInfo = BrainFunctional::createRandomFunc(Tools::random(1, 5));
            outMap.insert("connexionInfo", newConnexionInfo);
            return outMap;
        }

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
                            QString::number(constValue->mutate(nodePart[1].toFloat())));
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
