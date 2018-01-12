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

#include "mutationsmanager.h"

#include <QJsonObject>
#include <QJsonArray>
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
#include "sensors/boxsmellsensor.h"
#include "sensors/distancesensor.h"

// effectors
#include "effectors/effector.h"
#include "effectors/rotationalmotorseffector.h"
#include "effectors/grippereffector.h"
#include "effectors/flyingeffector.h"

namespace GeneCraftCore {

    MutationsManager::MutationsManager()
    {
        // --------------------
        // -- BODY MUTATIONS --
        // --------------------

        // Bone Length
        boneLength = new FloatMutation();
        boneLength->probability  = 1.0;
        boneLength->mean         = 0.0;
        boneLength->sigma        = 0.02;
        boneLength->minValue     = 0.1;
        boneLength->maxValue     = 5.0;

        // Bone radius mutation
        boneRadius = new FloatMutation();
        boneRadius->probability  = 1.0;
        boneRadius->mean         = 0.0;
        boneRadius->sigma        = 0.02;
        boneRadius->minValue     = 0.1;
        boneRadius->maxValue     = 2.0;

        // Fixation radius mutation
        fixRadius = new FloatMutation();
        fixRadius->probability   = 1.0;
        fixRadius->mean          = 0.0;
        fixRadius->sigma         = 0.02;
        fixRadius->minValue      = 0.1;
        fixRadius->maxValue      = 2.0;

        // Bone angular origin (Yaw and Roll)
        boneAngularOrigin = new FloatMutation();
        boneAngularOrigin->probability   = 0.70;
        boneAngularOrigin->mean         = 0.0;
        boneAngularOrigin->sigma        = 0.01;
        boneAngularOrigin->minValue      = -SIMD_PI;
        boneAngularOrigin->maxValue      =  SIMD_PI;

        // Bone angular limits (x,y,z for lower and upper)
        boneAngularLimits = new BoneLimitsMutation();

        // sensors
        sensorsStructural = new StructuralMutation();
        sensorsStructural->addProbability = 0.01f;
        sensorsStructural->deleteProbability = 0.012f;
        sensorsStructural->replaceProbability = 0.01f;
        sensorsStructuralList = new StructuralList();
        sensorsStructuralList->elements.append(new MutationElement("Accelerometer sensor",accelerometerSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Gyroscopic sensor",gyroscopicSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Egocentric sensor",positionSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Contact sensor",contactSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Box smell sensor",boxSmellSensor,0));
        sensorsStructuralList->elements.append(new MutationElement("Distance sensor",distanceSensor,1.0));

        // TODO serialize and add to ui
        distanceSensorYZ = new FloatMutation();
        distanceSensorYZ->probability   = 1.0;
        distanceSensorYZ->mean         = 0.0;
        distanceSensorYZ->sigma        = 0.02;
        distanceSensorYZ->minValue      = -SIMD_PI;
        distanceSensorYZ->maxValue      =  SIMD_PI;

        // effectors
        effectorsStructural = new StructuralMutation();
        effectorsStructural->enable = false;
        effectorsStructural->addProbability = 0.01f;
        effectorsStructural->deleteProbability = 0.012f;
        effectorsStructural->replaceProbability = 0.01f;
        effectorsStructuralList = new StructuralList();
        effectorsStructuralList->elements.append(new MutationElement("Gripper effector",gripperEffector,1.0));
        effectorsStructuralList->elements.append(new MutationElement("Flying effector",flyingEffector,1.0));

        // bones
        bonesStructural = new StructuralMutation();
        bonesStructural->addProbability = 0.01f;
        bonesStructural->deleteProbability = 0.02f;
        bonesStructural->replaceProbability = 0.01f;

        // ---------------------
        // -- BRAIN MUTATIONS --
        // ---------------------

        // Position X of Input
        brainInPos = new FloatMutation();
        brainInPos->probability = 1.0;
        brainInPos->mean         = 0.0;
        brainInPos->sigma        = 0.02;
        brainInPos->minValue    = 0;
        brainInPos->maxValue    = 1;

        // BrainWeight
        brainWeight = new FloatMutation();
        brainWeight->probability = 1.0;
        brainWeight->mean         = 0.0;
        brainWeight->sigma        = 0.02;
        brainWeight->minValue   = -1.0;
        brainWeight->maxValue   =  1.0;

        // Brain memory size
        brainMemorySize = new IntegerMutation();
        brainMemorySize->probability    = 0.05;
        brainMemorySize->minIncr        = -5;
        brainMemorySize->maxIncr        =  5;
        brainMemorySize->minValue       = 1;
        brainMemorySize->maxValue       = 100;

        // Brain frequency
        brainFrequency = new IntegerMutation();
        brainFrequency->probability     = 0.05;
        brainFrequency->minIncr      = -2;
        brainFrequency->maxIncr      =  2;
        brainFrequency->minValue     =  1;
        brainFrequency->maxValue     = 60;

        // New brain tree probability
        brainStructural = new StructuralMutation();
        brainStructural->addProbability = 0.01;
        brainStructural->deleteProbability = 0.02;
        brainStructural->replaceProbability = 0.01;

        brainNodeList = new StructuralList();
        brainNodeList->elements.append(new MutationElement("a + b", 0, 1));
        brainNodeList->elements.append(new MutationElement("a * b", 1, 1));
        brainNodeList->elements.append(new MutationElement("a / b", 2, 0));
        brainNodeList->elements.append(new MutationElement("atan2(a, b)", 3, 1));
        brainNodeList->elements.append(new MutationElement("(a > b) ? a : 0", 4, 1));
        brainNodeList->elements.append(new MutationElement("(a > b) ? a : b", 5, 1));
        brainNodeList->elements.append(new MutationElement("(a > 0) ? b : c", 6, 1));
        brainNodeList->elements.append(new MutationElement("cos(a)", 7, 1));
        brainNodeList->elements.append(new MutationElement("sin(a)", 8, 1));
        brainNodeList->elements.append(new MutationElement("abs(a)", 9, 1));
        brainNodeList->elements.append(new MutationElement("sign(a)", 10, 1));
        brainNodeList->elements.append(new MutationElement("log(a)", 11, 1));
        brainNodeList->elements.append(new MutationElement("a*a", 12, 1));
        brainNodeList->elements.append(new MutationElement("sigmoid(a)", 13, 1));
        brainNodeList->elements.append(new MutationElement("wave(freq : a, offset : b)", 14, 4));
        brainNodeList->elements.append(new MutationElement("memory : a", 15, 2));
        brainNodeList->elements.append(new MutationElement("smooth : a", 16, 2));
        brainNodeList->elements.append(new MutationElement("integrate : a", 17, 2));
        brainNodeList->elements.append(new MutationElement("interpolate : a", 18, 2));
        brainNodeList->elements.append(new MutationElement("max : a", 19, 2));
        brainNodeList->elements.append(new MutationElement("min : a", 20, 2));
        brainNodeList->elements.append(new MutationElement("diff : a", 21, 2));

        // Brain constant value
        constValue = new FloatMutation();
        constValue->probability  = 1.0;
        constValue->mean         = 0.0;
        constValue->sigma        = 0.03;
        constValue->minValue = -10;
        constValue->maxValue = 10;

        brainDistance = new FloatMutation();
        brainDistance->probability = 1.0;
        brainDistance->mean         = -0.01;
        brainDistance->sigma        = 0.02;
        brainDistance->minValue = 0.0;
        brainDistance->maxValue = 1.0;
    }

    MutationsManager::MutationsManager(QJsonObject map)
    {

        // --------------------
        // -- BODY MUTATIONS --
        // --------------------
        boneLength = new FloatMutation(map["boneLength"].toObject());
        boneRadius = new FloatMutation(map["boneRadius"].toObject());
        fixRadius = new FloatMutation(map["fixRadius"].toObject());
        boneAngularOrigin = new FloatMutation(map["boneAngularOrigin"].toObject());
        boneAngularLimits = new BoneLimitsMutation();
        delete boneAngularLimits->axisMutation;
        boneAngularLimits->axisMutation = new FloatMutation(map["boneAngularLimits"].toObject());

        // sensors
        sensorsStructural = new StructuralMutation(map["sensorsStructural"].toObject());
        sensorsStructuralList = new StructuralList(map["sensorsStructuralList"].toArray());

        // effectors
        effectorsStructural = new StructuralMutation(map["effectorsStructural"].toObject());
        effectorsStructuralList = new StructuralList(map["effectorsStructuralList"].toArray());

        // TODO serialize and add to ui
        distanceSensorYZ = new FloatMutation();
        distanceSensorYZ->probability   = 0.9;
        distanceSensorYZ->mean         = 0.0;
        distanceSensorYZ->sigma        = 0.02;
        distanceSensorYZ->minValue      = -SIMD_PI;
        distanceSensorYZ->maxValue      =  SIMD_PI;

        // bones
        bonesStructural = new StructuralMutation(map["bonesStructural"].toObject());

        // ---------------------
        // -- BRAIN MUTATIONS --
        // ---------------------

        // Plug grid size
        brainInPos = new FloatMutation(map["brainInPos"].toObject());
        brainWeight = new FloatMutation(map["brainWeight"].toObject());
        brainDistance = new FloatMutation(map["brainDistance"].toObject());
        brainMemorySize = new IntegerMutation(map["brainMemorySize"].toObject());
        brainFrequency = new IntegerMutation(map["brainFrequency"].toObject());
        constValue = new FloatMutation(map["constValue"].toObject());
        brainNodeList = new StructuralList(map["brainNodes"].toArray());
        brainStructural = new StructuralMutation(map["brainStruct"].toObject());
        if(brainNodeList->elements.size() < 22) {
            qDebug() << "adding wave to the list of mutations !";
            brainNodeList->elements.append(new MutationElement("wave : a", 22, 4));
        }
    }
    MutationsManager::~MutationsManager(){
        delete boneLength;
        delete boneRadius;
        delete fixRadius;
        delete boneAngularOrigin;
        delete boneAngularLimits;

        // sensors
        delete sensorsStructural;
        delete sensorsStructuralList;
        delete effectorsStructural;
        delete effectorsStructuralList;

        delete distanceSensorYZ;
        // bones
        delete bonesStructural;

        // ---------------------
        // -- BRAIN MUTATIONS --
        // ---------------------

        // Plug grid size
        delete brainInPos;
        delete brainWeight;
        delete brainDistance;
        delete brainMemorySize;
        delete brainFrequency;
        delete constValue;
        delete brainNodeList;
        delete brainStructural;


    }

    QJsonObject MutationsManager::serialize(){

        QJsonObject map;

        map.insert("boneLength",boneLength->serialize());
        map.insert("boneRadius",boneRadius->serialize());
        map.insert("boneAngularOrigin",boneAngularOrigin->serialize());
        map.insert("boneAngularLimits",boneAngularLimits->axisMutation->serialize());
        map.insert("bonesStructural",bonesStructural->serialize());

        map.insert("fixRadius",fixRadius->serialize());

        map.insert("sensorsStructural",sensorsStructural->serialize());
        map.insert("sensorsStructuralList",sensorsStructuralList->serialize());

        map.insert("effectorsStructural",effectorsStructural->serialize());
        map.insert("effectorsStructuralList",effectorsStructuralList->serialize());

        map.insert("brainInPos",brainInPos->serialize());
        map.insert("brainWeight",brainWeight->serialize());
        map.insert("brainDistance", brainDistance->serialize());
        map.insert("brainMemorySize",brainMemorySize->serialize());
        map.insert("brainFrequency",brainFrequency->serialize());
        map.insert("constValue",constValue->serialize());
        map.insert("brainNodes", brainNodeList->serialize());
        map.insert("brainStruct", brainStructural->serialize());

        return map;
    }

    QJsonObject MutationsManager::mutateEntity(const QJsonObject &map) {
        QJsonObject entityMap = QJsonObject(map);
        QJsonObject originsMap =  entityMap["origins"].toObject();
        QJsonObject bodyMap = entityMap["body"].toObject();
        QJsonObject treeShapeMap = bodyMap["shape"].toObject();
        QJsonObject brainMap = entityMap["brain"].toObject();
        int generation = entityMap["generation"].toInt();
        entityMap.insert("generation", generation+1);

        // treeshape mutation
        QJsonObject newTreeShapeMap = this->mutateTreeShape(treeShapeMap);
        bodyMap.remove("shape");
        bodyMap.insert("shape",   newTreeShapeMap);
        entityMap.insert("body",  bodyMap);

        // brain mutation
        QJsonObject newBrainMap     = this->mutateBrain(brainMap);
        entityMap.remove("brain");
        entityMap.insert("brain", newBrainMap);

        // next generation
        originsMap.insert("generation", originsMap["generation"].toInt()+1);
        entityMap.remove("origins");
        entityMap.insert("origins", originsMap);

        return entityMap;
    }

    QJsonObject MutationsManager::mutateTreeShape(const QJsonObject &map)
    {
        // clone
        QJsonObject treeShapeMap = QJsonObject(map);

        // mutate the root fix
        QJsonObject rootFixMap = treeShapeMap.value("rootFix").toObject();
        rootFixMap = mutateFixation(rootFixMap);

        // mutate all bones
        QJsonArray newBonesList;
        foreach(QJsonValue boneVariant, rootFixMap.value("bones").toArray()) {
            QJsonObject boneMap = boneVariant.toObject();
            newBonesList.append(recursiveMutateTreeShape(boneMap));
        }

        // add new bone to fix
        if(bonesStructural->checkAdd())
            addBone(newBonesList);

        rootFixMap.remove("bones");
        rootFixMap.insert("bones",newBonesList);
        treeShapeMap.remove("rootFix");
        treeShapeMap.insert("rootFix",rootFixMap);
        return treeShapeMap;
    }

    QJsonObject MutationsManager::recursiveMutateTreeShape(QJsonObject &boneVariant) {

        // mutate bone
        boneVariant = mutateBone(boneVariant);

        // mutate the end fix
        QJsonObject endFixMap = boneVariant.value("endFix").toObject(); // COPY !
        endFixMap = mutateFixation(endFixMap);

        // mutate all bones
        QJsonArray newBonesList;
        foreach(QJsonValue boneVariant, endFixMap.value("bones").toArray()) {
            QJsonObject boneMap = boneVariant.toObject();
            newBonesList.append(recursiveMutateTreeShape(boneMap));
        }
        // add new bone to fix
        if(bonesStructural->checkAdd())
             addBone(newBonesList);

        endFixMap.remove("bones");
        endFixMap.insert("bones",newBonesList);
        boneVariant.remove("endFix");
        boneVariant.insert("endFix",endFixMap);

        return boneVariant;
    }

    QJsonObject MutationsManager::mutateBone(const QJsonObject &map){
        QJsonObject boneMap = QJsonObject(map);
        // ----------
        // -- size --
        // ----------

        // length mutation
        boneLength->mutate(boneMap, "length");

        // radius mutation
        boneRadius->mutate(boneMap, "radius");

        // --------------------
        // -- angular origin --
        // --------------------
        QJsonObject localRotation = boneMap["localRotation"].toObject();
        boneAngularOrigin->mutate(localRotation,"y");
        boneAngularOrigin->mutate(localRotation,"z");
        boneMap.remove("localRotation");
        boneMap.insert("localRotation",localRotation);

        // --------------------
        // -- angular limits --
        // --------------------

        QJsonObject lowerLimits = boneMap["lowerLimits"].toObject();
        QJsonObject upperLimits = boneMap["upperLimits"].toObject();

        boneAngularLimits->mutate(lowerLimits,upperLimits);

        boneMap.remove("lowerLimits");
        boneMap.remove("upperLimits");
        boneMap.insert("lowerLimits",lowerLimits);
        boneMap.insert("upperLimits",upperLimits);

        // ----------------------
        // -- motors mutations --
        // ----------------------
        QJsonObject newMuscle = boneMap["muscle"].toObject();
        QJsonObject newMotors;
        QJsonObject motors = newMuscle["outs"].toObject();

        QString allAxis[] = {"x","y","z"};
        // foreach motor axis...
        for(int i=0; i<3; ++i){

            // get motor name
            QString motor = allAxis[i];

            // if motor exists
            if(motors.contains(motor))
            {
                // need to delete motor ?
                if(lowerLimits[motor].toDouble() == 0.0f && upperLimits[motor].toDouble() == 0.0f) {
                    continue; // not insert in newMotors
                }

                QJsonObject motorMap = motors[motor].toObject();

                // new version
                if(motorMap.contains("contractionOutput")) {
                    QJsonObject newContraction = mutateBrainOut(motorMap["contractionOutput"].toObject());
                    QJsonObject newExpansion   = mutateBrainOut(motorMap["expansionOutput"].toObject());
                    motorMap.remove("contractionOutput");
                    motorMap.remove("expansionOutput");
                    motorMap.insert("contractionOutput", newContraction);
                    motorMap.insert("expansionOutput",   newExpansion);
                    newMotors.remove(motor);
                    newMotors.insert(motor,motorMap);
                }
                // old version (convert in new version)
                else {

                    // mutate all brainouts
                    QJsonArray brainOuts = motorMap["brainOuts"].toArray();

                    QJsonObject newContraction = mutateBrainOut(brainOuts[0].toObject());
                    QJsonObject newExpansion   = mutateBrainOut(brainOuts[1].toObject());
                    motorMap.insert("contractionOutput", newContraction);
                    motorMap.insert("expansionOutput",   newExpansion);
                    motorMap.remove("brainOuts");

                    newMotors.remove(motor);
                    newMotors.insert(motor,motorMap);
                }

            } else {

                // need to create a new motor ?
                if(lowerLimits[motor].toDouble() != 0.0f || upperLimits[motor].toDouble() != 0.0f) {
                   newMotors.insert(motor,BrainOutMotor::generateEmpty());
                }
            }
        }

        newMuscle.remove("outs");
        newMuscle.insert("outs",newMotors);
        boneMap.remove("muscle");
        boneMap.insert("muscle",newMuscle);

        return boneMap;
    }

    QJsonObject MutationsManager::mutateFixation(const QJsonObject &map){
        QJsonObject fixMap = QJsonObject(map);
        // radius mutation
        fixRadius->mutate(fixMap, "radius");

        // -----------------------
        // -- Sensors mutations --
        // -----------------------
        QJsonArray sensorList = fixMap["sensors"].toArray();
        QJsonArray newSensorList;

        // remove / replace
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
        foreach(QJsonValue sensor, sensorList) {
            QJsonObject sensorMap = sensor.toObject();

            switch((SensorType) sensorMap["type"].toInt()) {
                case accelerometerSensor:
                    sensorMap.insert("inputX", mutateBrainIn(sensorMap["inputX"].toObject()));
                    sensorMap.insert("inputY", mutateBrainIn(sensorMap["inputY"].toObject()));
                    sensorMap.insert("inputZ", mutateBrainIn(sensorMap["inputZ"].toObject()));
                    break;
                case gyroscopicSensor:
                    sensorMap.insert("inputPitch", mutateBrainIn(sensorMap["inputPitch"].toObject()));
                    sensorMap.insert("inputYaw",   mutateBrainIn(sensorMap["inputYaw"].toObject()));
                    sensorMap.insert("inputRoll",  mutateBrainIn(sensorMap["inputRoll"].toObject()));
                    break;
                case positionSensor:
                    sensorMap.insert("inputX", mutateBrainIn(sensorMap["inputX"].toObject()));
                    sensorMap.insert("inputY", mutateBrainIn(sensorMap["inputY"].toObject()));
                    sensorMap.insert("inputZ", mutateBrainIn(sensorMap["inputZ"].toObject()));
                    break;
                case contactSensor:
                    sensorMap.insert("collisionInput", mutateBrainIn(sensorMap["collisionInput"].toObject()));
                    break;
                case boxSmellSensor:
                    sensorMap.insert("intensityInput", mutateBrainIn(sensorMap["intensityInput"].toObject()));
                    // TODO mutate radius of smell...
                    break;
                case distanceSensor:
                    sensorMap.insert("distanceInput", mutateBrainIn(sensorMap["distanceInput"].toObject()));
                    QJsonObject orientationMap = sensorMap["orientation"].toObject();
                    distanceSensorYZ->mutate(orientationMap,"y");
                    distanceSensorYZ->mutate(orientationMap,"z");
                    sensorMap.insert("orientation",orientationMap);
                   break;
            }

            newSensorList.append(sensorMap);
        }

        // add sensor ?
        if(sensorsStructural->checkAdd())
            addSensor(newSensorList);

        fixMap.remove("sensors");
        fixMap.insert("sensors", newSensorList);


        // ------------------------
        // -- Effector mutations --
        // ------------------------
        QJsonArray effectorList = fixMap["effectors"].toArray();
        QJsonArray newEffectorsList;

        // remove / replace
        int nbEffectors = effectorList.count();
        for(int i=0;i<nbEffectors;++i) {

           // delete sensor
           if(effectorsStructural->checkDelete()) {
                effectorList.removeAt(i);
                i--;
                nbEffectors--;
           }
           // replace sensor
           else if(effectorsStructural->checkReplace()) {
               effectorList.removeAt(i);
               addEffector(effectorList,i);
           }
        }

        // if motor exists
        foreach(QJsonValue effector, effectorList) {
            QJsonObject effectorMap = effector.toObject();

            switch((EffectorType) effectorMap["type"].toInt()) {
                case rotationalMotorEffector:
                    // do in bone mutation...
                    break;
                case gripperEffector :
                    effectorMap.insert("gripperOutput", mutateBrainOut(effectorMap["gripperOutput"].toObject()));
                    break;
                case flyingEffector :
                    effectorMap.insert("impulseX", mutateBrainOut(effectorMap["impulseX"].toObject()));
                    effectorMap.insert("impulseY", mutateBrainOut(effectorMap["impulseY"].toObject()));
                    effectorMap.insert("impulseZ", mutateBrainOut(effectorMap["impulseZ"].toObject()));
                    break;
            }

            newEffectorsList.append(effectorMap);
        }

        // add effector ?
        if(effectorsStructural->checkAdd())
            addEffector(newEffectorsList);

        fixMap.remove("effectors");
        fixMap.insert("effectors", newEffectorsList);


        // ---------------------
        // -- Bones mutations --
        // ---------------------
        QJsonArray bonesList = fixMap["bones"].toArray();

        for(int i=0;i<bonesList.count();++i) {
           // Delete
           if(bonesStructural->checkDelete()) {
                QJsonObject boneMap = bonesList.takeAt(i).toObject();
                QJsonObject fixMap = boneMap["endFix"].toObject();
                QJsonArray bones = fixMap["bones"].toArray();
                bonesList.append(bones);
                i--;
           }
           // Insert
           else if(bonesStructural->checkAdd()) {
               // Un copie de l'os prÃ©cÃ©dent est plus intÃ©ressante qu'un os totalement random
               // The new bone
               QJsonValue oldBone = bonesList.takeAt(i);
               QJsonObject newBoneMap = oldBone.toObject();
               this->boneLength->mutate(newBoneMap, "length");
               this->boneRadius->mutate(newBoneMap, "radius");

               // And his fixation
               QJsonObject newEndFixation = newBoneMap["endFix"].toObject();
               this->fixRadius->mutate(newEndFixation, "radius");

               // The son
               QJsonArray newBones;
               newBones.append(oldBone);
               newEndFixation.remove("bones");
               newEndFixation.insert("bones", newBones);
               newBoneMap.remove("endFix");
               newBoneMap.insert("endFix", newEndFixation);

               // Adding the child to the parent
               bonesList.insert(i, newBoneMap);

           }
           // Replace
           else if(bonesStructural->checkReplace()) {
               QJsonObject boneMap = bonesList.takeAt(i).toObject();
               QJsonObject endFix = boneMap["endFix"].toObject();
               addBone(bonesList,i, endFix); // Took the old endFix back
           }
        }

        // --
        // (?) adding of bone : after bone mutation to avoid recurcive calls
        // (you add a bone then the end fix of this bone will be also mutated...)
        // see : recursiveMutateTreeShape(...)
        // --

        fixMap.remove("bones");
        fixMap.insert("bones", bonesList);

        return fixMap;
    }

    void MutationsManager::addBone(QJsonArray &bonesList, int i, QJsonObject endFix) {
        QJsonObject newBone = Bone::generateEmpty();

        if(endFix != QJsonObject()) {
            newBone.remove("endFix");
            newBone.insert("endFix", endFix);
        }

        // insert in a specific position
        if(i > -1 && i < bonesList.count())
            bonesList.insert(i,newBone);
        else
            bonesList.append(newBone);
    }

    // add sensor
    void MutationsManager::addSensor(QJsonArray &sensorsList, int i) {

        MutationElement *me = sensorsStructuralList->pickOne();
        QJsonObject newSensor;

        switch((SensorType) me->type) {
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
            case boxSmellSensor:
                newSensor = BoxSmellSensor::generateEmpty();
                break;
            case distanceSensor :
                newSensor = DistanceSensor::generateEmpty();
                break;
        }

        // insert in a specific position
        if(i > -1 && i < sensorsList.count())
            sensorsList.insert(i,newSensor);
        else
            sensorsList.append(newSensor);
    }

    // add effector
    void MutationsManager::addEffector(QJsonArray &effectorsList, int i) {

        MutationElement *me = effectorsStructuralList->pickOne();
        QJsonObject newEffector;

        switch((EffectorType) me->type) {
            case rotationalMotorEffector:
                // impossible, not in effectorsStructuralList!
                qDebug() << Q_FUNC_INFO << "RotationalMotorEffector must to be in effectorsStructuralList !";
            break;
            case gripperEffector:
                newEffector = GripperEffector::generateEmpty();
                break;
            case flyingEffector:
                newEffector = FlyingEffector::generateEmpty();
                break;
        }

        // insert in a specific position
        if(i > -1 && i < effectorsList.count())
            effectorsList.insert(i,newEffector);
        else
            effectorsList.append(newEffector);
    }


    // Mutate the brain
    QJsonObject MutationsManager::mutateBrain(QJsonObject brain) {
        brainFrequency->mutate(brain, "frequency");
        return brain;
    }

    // Mutate a brainInput
    QJsonObject MutationsManager::mutateBrainIn(QJsonObject brainIn) {
        // "inputRoll":{"connexions":[{"w":-0.0762658,"x":0.471847,"y":0.920957}
        QJsonArray connexions = brainIn["connexions"].toArray();
        QJsonArray newConnexions;

        foreach(QJsonValue connexion, connexions) {
            // To map !
            QJsonObject connexionMap = connexion.toObject();

            // mutation of position
            brainInPos->mutate(connexionMap, "x");
            brainInPos->mutate(connexionMap, "y");

            // mutation of weight
            brainWeight->mutate(connexionMap, "w");

            // mutation of distance
            brainDistance->mutate(connexionMap, "d");
            newConnexions.append(connexionMap);
        }

        brainIn.remove("connexions");
        brainIn.insert("connexions", newConnexions);

        return brainIn;
    }

    // Mutate a brainOutput
    QJsonObject MutationsManager::mutateBrainOut(QJsonObject brainOut) {
        QString treeData = brainOut["connexionInfo"].toString();
        QStringList nodes = treeData.split(",", QString::SkipEmptyParts);
        QString newConnexionInfo;

        QList<QString>::iterator it = nodes.begin();
        while(it != nodes.end()){
            // replace the entire subtree
            if(brainStructural->checkReplace()) {
                this->consumnSubTree(it);
                newConnexionInfo.append(BrainFunctional::createRandomFunc(2, brainNodeList));
                continue;
            } else if(brainStructural->checkDelete()) {
                this->consumnSubTree(it);
                newConnexionInfo.append(BrainFunctional::createRandomFunc(1));
                continue;
            } else if(brainStructural->checkAdd()) {
                int subchoice = brainNodeList->pickOne()->type;
                int nbsub = 0;
                int maxmem = qrand() % 100 + 1;
                switch(subchoice) {
                case 0:
                    newConnexionInfo.append("+,");
                    nbsub += 2;
                    break;
                case 1:
                    newConnexionInfo.append("*,");
                    nbsub += 2;
                    break;
                case 2:
                    newConnexionInfo.append("/,");
                    nbsub += 2;
                    break;
                case 3:
                    newConnexionInfo.append("ATAN,");
                    nbsub += 2;
                    break;
                case 4:
                    newConnexionInfo.append("T,");
                    nbsub += 2;
                    break;
                case 5:
                    newConnexionInfo.append(">,");
                    nbsub += 3;
                    break;
                case 6:
                    newConnexionInfo.append("IF,");
                    nbsub += 3;
                    break;
                case 7:
                    newConnexionInfo.append("COS,");
                    nbsub += 1;
                    break;
                case 8:
                    newConnexionInfo.append("SIN,");
                    nbsub += 1;
                    break;
                case 9:
                    newConnexionInfo.append("ABS,");
                    nbsub += 1;
                    break;
                case 10:
                    newConnexionInfo.append("SIGN,");
                    nbsub += 1;
                    break;
                case 11:
                    newConnexionInfo.append("LOG,");
                    nbsub += 1;
                    break;
                case 12:
                    newConnexionInfo.append("EXP,");
                    nbsub += 1;
                    break;
                case 13:
                    newConnexionInfo.append("SIGM,");
                    nbsub += 1;
                    break;
                case 14:
                    newConnexionInfo.append("SINUS,");
                    nbsub += 2;
                    break;
                case 15:
                    newConnexionInfo.append("MEM ");
                    newConnexionInfo.append(" " + QString::number(maxmem) + ",");
                    nbsub += 1;
                    break;
                case 16:
                    newConnexionInfo.append("SMOOTH");
                    newConnexionInfo.append(" " + QString::number(maxmem) + ",");
                    nbsub += 1;
                    break;
                case 17:
                    newConnexionInfo.append("INT");
                    newConnexionInfo.append(" " + QString::number(maxmem) + ",");
                    nbsub += 1;
                    break;
                case 18:
                    newConnexionInfo.append("INTERPOLATE");
                    newConnexionInfo.append(" " + QString::number(maxmem) + ",");
                    nbsub += 1;
                    break;
                case 19:
                    newConnexionInfo.append("MAX");
                    newConnexionInfo.append(" " + QString::number(maxmem) + ",");
                    nbsub += 1;
                    break;
                case 20:
                    newConnexionInfo.append("MIN");
                    newConnexionInfo.append(" " + QString::number(maxmem) + ",");
                    nbsub += 1;
                    break;
                case 21:
                    newConnexionInfo.append("DIFF");
                    newConnexionInfo.append(" " + QString::number(maxmem) + ",");
                    nbsub += 1;
                    break;
                }

                nbsub--;
                // The actual tree
                while(it != nodes.end()) {
                    newConnexionInfo.append(*it);
                    newConnexionInfo.append(",");
                    it++;
                }
                // The missings params
                while(nbsub) {
                    nbsub--;
                    newConnexionInfo.append(BrainFunctional::createRandomFunc(1));
                }

                continue;
            }

            QString node = *it;
            it++;
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
            case INPUT:
                // x et y
                newConnexionInfo.append(nodePart[0]);
                newConnexionInfo.append(" " +
                            QString::number(brainInPos->mutate(nodePart[1].toDouble())));
                newConnexionInfo.append(" " +
                            QString::number(brainInPos->mutate(nodePart[2].toDouble())));
                newConnexionInfo.append(",");
                break;
            case CONSTANT:
                newConnexionInfo.append(nodePart[0]);
                newConnexionInfo.append(" " +
                            QString::number(constValue->mutate(nodePart[1].toDouble())));
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
            case WAVE:
                newConnexionInfo.append(nodePart[0]);
                newConnexionInfo.append(" " +
                            QString::number(constValue->mutate(nodePart[1].toDouble())));
                newConnexionInfo.append(",");
                break;

            case MEMORY_SPACE:
            case BAD_TYPE:
                qDebug() << "SHOULD NOT BE IN STRING memoryspace or badtype !!";
                break;
            }
        }

        brainOut.remove("connexionInfo");
        brainOut.insert("connexionInfo", newConnexionInfo);

        return brainOut;
    }

    void MutationsManager::consumnSubTree(QStringList::iterator &it) {
        QString node = *it;
        it++;
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
                this->consumnSubTree(it);
                this->consumnSubTree(it);
                break;
            case GT:
            // 3 operands
            case IFELSE:
                this->consumnSubTree(it);
                this->consumnSubTree(it);
                this->consumnSubTree(it);
                break;
            // 1 operand
            case COS:
            case SIN:
            case ABS:
            case SIGN_OF:
            case LOG:
            case EXP:
            case SIGM:
                this->consumnSubTree(it);
                break;
            case INPUT:
            case CONSTANT:
            case WAVE:
                break;
            case INTEGRATE:
            case INTERPOLATE:
            case DIFFERENTIATE:
            case MEMORY:
            case SMOOTH:
            case MIN:
            case MAX:
                this->consumnSubTree(it);
                break;
            case SINUS:
                this->consumnSubTree(it);
                this->consumnSubTree(it);
                break;
            case MEMORY_SPACE:
            case BAD_TYPE:
                qDebug() << "SHOULD NOT BE IN STRING memoryspace or badtype !!";
                break;
        }
    }
}
