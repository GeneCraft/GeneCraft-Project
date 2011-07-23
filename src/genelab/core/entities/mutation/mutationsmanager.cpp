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
#include "sensors/boxsmellsensor.h"
#include "sensors/distancesensor.h"

// effectors
#include "effectors/effector.h"
#include "effectors/rotationalmotorseffector.h"
#include "effectors/grippereffector.h"
#include "effectors/flyingeffector.h"

#include "qxtjson.h"

namespace GeneLabCore {

    MutationsManager::MutationsManager()
    {
        // --------------------
        // -- BODY MUTATIONS --
        // --------------------

        // Bone Length
        boneLength = new FloatMutation();
        boneLength->probability  = 0.05;
        boneLength->minFact      = -0.05;
        boneLength->maxFact      =  0.05;
        boneLength->minValue     = 0.1;
        boneLength->maxValue     = 5.0;

        // Bone radius mutation
        boneRadius = new FloatMutation();
        boneRadius->probability  = 0.05;
        boneRadius->minFact      = -0.05;
        boneRadius->maxFact      =  0.05;
        boneRadius->minValue     = 0.1;
        boneRadius->maxValue     = 2.0;

        // Fixation radius mutation
        fixRadius = new FloatMutation();
        fixRadius->probability   = 0.05;
        fixRadius->minFact       = -0.05;
        fixRadius->maxFact       =  0.05;
        fixRadius->minValue      = 0.1;
        fixRadius->maxValue      = 2.0;

        // Bone angular origin (Yaw and Roll)
        boneAngularOrigin = new FloatMutation();
        boneAngularOrigin->probability   = 0.05;
        boneAngularOrigin->minFact       = -0.01;
        boneAngularOrigin->maxFact       =  0.01;
        boneAngularOrigin->minValue      = -M_PI;
        boneAngularOrigin->maxValue      =  M_PI;

        // Bone angular limits (x,y,z for lower and upper)
        boneAngularLimits = new BoneLimitsMutation();

        // sensors
        sensorsStructural = new StructuralMutation();
        sensorsStructural->addProbability = 0.01f;
        sensorsStructural->deleteProbability = 0.02f;
        sensorsStructural->replaceProbability = 0.01f;
        sensorsStructuralList = new StructuralList();
        sensorsStructuralList->elements.append(new MutationElement("Accelerometer sensor",accelerometerSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Gyroscopic sensor",gyroscopicSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Egocentric sensor",positionSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Contact sensor",contactSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Box smell sensor",boxSmellSensor,1.0));
        sensorsStructuralList->elements.append(new MutationElement("Distance sensor",distanceSensor,1.0));

        // TODO serialize and add to ui
        distanceSensorYZ = new FloatMutation();
        distanceSensorYZ->probability   = 0.05;
        distanceSensorYZ->minFact       = -0.01;
        distanceSensorYZ->maxFact       =  0.01;
        distanceSensorYZ->minValue      = -M_PI;
        distanceSensorYZ->maxValue      =  M_PI;

        // effectors
        effectorsStructural = new StructuralMutation();
        effectorsStructural->addProbability = 0.0f;
        effectorsStructural->deleteProbability = 0.0f;
        effectorsStructural->replaceProbability = 0.0f;
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
        brainInPos->probability = 0.05;
        brainInPos->minFact     = -0.1;
        brainInPos->maxFact     =  0.1;
        brainInPos->minValue    = 0;
        brainInPos->maxValue    = 1;

        // BrainWeight
        brainWeight = new FloatMutation();
        brainWeight->probability = 0.05;
        brainWeight->minFact    = -0.1;
        brainWeight->maxFact    =  0.1;
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
        constValue->probability = 0.05;
        constValue->minFact = -0.1;
        constValue->maxFact = 0.1;
        constValue->minValue = -10;
        constValue->maxValue = 10;

        brainDistance = new FloatMutation();
        brainDistance->probability = 0.1;
        brainDistance->minFact = -0.3;
        brainDistance->maxFact = 0.1;
        brainDistance->minValue = 0.0;
        brainDistance->maxValue = 1.0;
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
        boneAngularLimits = new BoneLimitsMutation();
        delete boneAngularLimits->axisMutation;
        boneAngularLimits->axisMutation = new FloatMutation(map["boneAngularLimits"]);

        // sensors
        sensorsStructural = new StructuralMutation(map["sensorsStructural"]);
        sensorsStructuralList = new StructuralList(map["sensorsStructuralList"]);

        // effectors
        effectorsStructural = new StructuralMutation(map["effectorsStructural"]);
        effectorsStructuralList = new StructuralList(map["effectorsStructuralList"]);

        // TODO serialize and add to ui
        distanceSensorYZ = new FloatMutation();
        distanceSensorYZ->probability   = 0.05;
        distanceSensorYZ->minFact       = -0.01;
        distanceSensorYZ->maxFact       =  0.01;
        distanceSensorYZ->minValue      = -M_PI;
        distanceSensorYZ->maxValue      =  M_PI;

        // bones
        bonesStructural = new StructuralMutation(map["bonesStructural"]);

        // ---------------------
        // -- BRAIN MUTATIONS --
        // ---------------------

        // Plug grid size
        brainInPos = new FloatMutation(map["brainInPos"]);
        brainWeight = new FloatMutation(map["brainWeight"]);
        brainDistance = new FloatMutation(map["brainDistance"]);
        brainMemorySize = new IntegerMutation(map["brainMemorySize"]);
        brainFrequency = new IntegerMutation(map["brainFrequency"]);
        constValue = new FloatMutation(map["constValue"]);
        brainNodeList = new StructuralList(map["brainNodes"]);
        brainStructural = new StructuralMutation(map["brainStruct"]);
    }

    QVariant MutationsManager::serialize(){

        QVariantMap map;

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
        foreach(QVariant boneVariant, rootFixMap.value("bones").toList()) {
            newBonesList.append(recursiveMutateTreeShape(boneVariant));
        }

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
        QVariantMap newMuscle = boneMap["muscle"].toMap();
        QVariantMap newMotors;
        QVariantMap motors = newMuscle["outs"].toMap();

        QString allAxis[] = {"x","y","z"};
        // foreach motor axis...
        for(int i=0; i<3; ++i){

            // get motor name
            QString motor = allAxis[i];

            // if motor exists
            if(motors.contains(motor))
            {
                // need to delete motor ?
                if(lowerLimits[motor].toFloat() == 0.0f && upperLimits[motor].toFloat() == 0.0f) {
                    continue; // not insert in newMotors
                }

                QVariantMap motorMap = motors[motor].toMap();

                // new version
                if(motorMap.contains("contractionOutput")) {
                    motorMap.insert("contractionOutput", mutateBrainOut(motorMap["contractionOutput"]));
                    motorMap.insert("expansionOutput", mutateBrainOut(motorMap["expansionOutput"]));
                    newMotors.insert(motor,motorMap);
                }
                // old version (convert in new version)
                else {

                    // mutate all brainouts
                    QVariantList brainOuts = motorMap["brainOuts"].toList();

                    motorMap.insert("contractionOutput", mutateBrainOut(brainOuts[0]));
                    motorMap.insert("expansionOutput", mutateBrainOut(brainOuts[1]));
                    motorMap.remove("brainOuts");

                    newMotors.insert(motor,motorMap);
                }

            } else {

                // need to create a new motor ?
                if(lowerLimits[motor].toFloat() != 0.0f || upperLimits[motor].toFloat() != 0.0f) {
                   newMotors.insert(motor,BrainOutMotor::generateEmpty());
                }
            }
        }

        newMuscle.insert("outs",newMotors);
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
        foreach(QVariant sensor, sensorList) {
            QVariantMap sensorMap = sensor.toMap();

            switch((SensorType) sensorMap["type"].toInt()) {
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
                case boxSmellSensor:
                    sensorMap.insert("intensityInput", mutateBrainIn(sensorMap["intensityInput"]));
                    // TODO mutate radius of smell...
                    break;
                case distanceSensor:
                    sensorMap.insert("distanceInput", mutateBrainIn(sensorMap["distanceInput"]));
                    QVariantMap orientationMap = sensorMap["orientation"].toMap();
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

        fixMap.insert("sensors", newSensorList);


        // ------------------------
        // -- Effector mutations --
        // ------------------------
        QVariantList effectorList = fixMap["effectors"].toList();
        QVariantList newEffectorsList;

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
        foreach(QVariant effector, effectorList) {
            QVariantMap effectorMap = effector.toMap();

            switch((EffectorType) effectorMap["type"].toInt()) {
                case rotationalMotorEffector:
                    // do in bone mutation...
                    break;
                case gripperEffector :
                    effectorMap.insert("gripperOutput", mutateBrainOut(effectorMap["gripperOutput"]));
                    break;
                case flyingEffector :
                    effectorMap.insert("impulseX", mutateBrainOut(effectorMap["impulseX"]));
                    effectorMap.insert("impulseY", mutateBrainOut(effectorMap["impulseY"]));
                    effectorMap.insert("impulseZ", mutateBrainOut(effectorMap["impulseZ"]));
                    break;
            }

            newEffectorsList.append(effectorMap);
        }

        // add effector ?
        if(effectorsStructural->checkAdd())
            addEffector(newEffectorsList);

        fixMap.insert("effectors", newEffectorsList);


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

        MutationElement *me = sensorsStructuralList->pickOne();
        QVariant newSensor;

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
    void MutationsManager::addEffector(QVariantList &effectorsList, int i) {

        MutationElement *me = effectorsStructuralList->pickOne();
        QVariant newEffector;

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
    QVariant MutationsManager::mutateBrain(QVariant brain) {
        QVariantMap brainMap = brain.toMap();
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

            // mutation of distance
            brainDistance->mutate(connexionMap, "d");
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
            case IN:
            case CONST:
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
