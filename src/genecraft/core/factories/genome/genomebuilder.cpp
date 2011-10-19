#include "genomebuilder.h"

#include <QList>

#include "body/bone.h"
#include "body/fixation.h"
#include "body/treeshape.h"

#include "sensors/sensor.h"
#include "sensors/accelerometersensor.h"
#include "sensors/boxsmellsensor.h"
#include "sensors/contactsensor.h"
#include "sensors/distancesensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/positionsensor.h"
#include "sensors/smellsensor.h"

#include "effectors/effector.h"
#include "effectors/flyingeffector.h"
#include "effectors/grippereffector.h"
#include "effectors/rotationalmotorseffector.h"

namespace GeneCraftCore {

    GenomeBuilder::GenomeBuilder(QObject *parent) :
        QObject(parent)
    {
    }

    Entity *GenomeBuilder::buildEntity(QVariant genotype,
                                        btShapesFactory *shapesFactory,
                                        const btVector3 &initialPosition)
    {
        QVariantMap entityMap = genotype.toMap();

        // Entity & origins
        QVariantMap origins = entityMap.value("origins").toMap();
        Entity * entity = new Entity(origins.value("name").toString(),
                                      origins.value("family").toString(),
                                      "generic",
                                      origins.value("generation").toInt());
        // Brain
        entity->setBrain(new BrainFunctional(entityMap.value("brain")));

        // Body
        QVariantMap body = entityMap.value("body").toMap();
        if(body.value("shapeType").toString().compare(QString("TreeShape")) == 0)
        {
            TreeShape* treeShape = new TreeShape(shapesFactory);

            btTransform initTransform;
            initTransform.setIdentity();
            initTransform.setOrigin(initialPosition);

            Fixation* root = GenomeBuilder::buildRoot(shapesFactory, body.value("shape"), initTransform);
            treeShape->setRoot(root);
            entity->setShape(treeShape);

            QList<GenomeModifier*> modifiers;
            GenomeBuilder::buildElement(shapesFactory, root, modifiers, body.value("shape").toMap().value("rootFix"), NULL);
        }


        return entity;
    }


    Fixation*  GenomeBuilder::buildElement(btShapesFactory* shapesFactory, Fixation *parent,
                                      QList<GenomeModifier*> modifiers, QVariant genome, Bone* ref) {

        QVariantMap map = genome.toMap();

        // If it's not a bone nor a fixation
        // It should be a symmetry or a recursion
        if(map.contains("type")) {
            QString type = map["type"].toString();
            if(type == "symmetry") {
                // Create the symmetry modifier
                GenomeModifier* modifier = new GenomeModifier();
                modifier->setNeuralSymmetry(map["neuralSymmetry"].toFloat());
                modifier->setPhysicalSymmetry(map["physicalSymmetry"].toFloat());
                QList<GenomeModifier*> newModifiers;
                newModifiers.append(modifiers);
                newModifiers.append(modifier);

                // The symmetry element, for further modification / serialisation
                Symmetry* sym = new Symmetry();
                sym->physSymmetry = map["physicalSymmetry"].toFloat();
                sym->neuralSymmetry = map["neuralSymmetry"].toFloat();
                sym->modifiers.append(modifier);

                // Build the original child and the symmetric one, and we arbitrary return the new one
                Fixation* refFix = GenomeBuilder::buildElement(shapesFactory, parent, modifiers,  map["element"], ref);
                Fixation* last = GenomeBuilder::buildElement(shapesFactory, parent, newModifiers, map["element"], refFix->getParentBone());

                sym->model = refFix->getParentBone();
                sym->copy  = last->getParentBone();
                refFix->getParentBone()->setSymmetry(sym);
                return last;

            } else if (type == "recursive") {
                // Create the recursion modifier
                GenomeModifier* modifier = new GenomeModifier();
                modifier->setNeuralRotation(map["neuralAlpha"].toFloat(), map["neuralDelta"].toFloat());
                modifier->setPhysicalScale(map["physicalScale"].toFloat());
                QList<GenomeModifier*> newModifiers;
                newModifiers.append(modifiers);

                // The recursion element, for further modification / serialisation
                Recursion* rec = new Recursion();
                rec->depth       = map["depth"].toInt();
                rec->physScale   = map["physicalScale"].toFloat();
                rec->neuralAlpha = map["neuralAlpha"].toFloat();
                rec->neuralDelta = map["neuralDelta"].toFloat();
                rec->modifiers.append(modifier);

                // Construct the n-th recursions of the element
                int nb = map["depth"].toInt();
                Fixation* refFix = parent = GenomeBuilder::buildElement(shapesFactory, parent, newModifiers, map["element"], ref);
                refFix->getParentBone()->setRecursion(rec);
                rec->model = refFix->getParentBone();
                for(int i = 0; i < nb; i++) {
                    newModifiers.append(modifier);
                    parent = GenomeBuilder::buildElement(shapesFactory, parent, newModifiers, map["element"], refFix->getParentBone());
                    rec->childs << parent->getParentBone();
                }

                // Create the tail and add it to the rec
                Bone* tailRef = NULL;
                if(ref && ref->getRecursion()) {
                    tailRef = ref->getRecursion()->tail.first();
                }
                Fixation* last = GenomeBuilder::buildElement(shapesFactory, parent, modifiers, map["tail"], tailRef);
                rec->tail.append(last->getParentBone());
                return last;
            } else {
                qDebug() << "GenomeBuilder: Could not recognize the type !";
            }
        }

        // So it's a fix/bones
        if(map.contains("bones")) // Fixation
            return GenomeBuilder::buildFix(shapesFactory, parent, modifiers, genome, ref);
        else if(map.contains("endFix")) // Bone
            return GenomeBuilder::buildBone(shapesFactory, parent, modifiers, genome, ref);
    }

    Fixation*  GenomeBuilder::buildBone(btShapesFactory* shapesFactory, Fixation *parent,
                                       QList<GenomeModifier*> modifiers, QVariant boneGenome, Bone* ref) {

        // We apply the actual modifiers to this genome element
        foreach(GenomeModifier* modifier, modifiers)
            boneGenome = modifier->modify(boneGenome);

        QVariantMap boneMap = boneGenome.toMap();

        // Radius & lenght
        btScalar boneRadius = boneMap.value("radius").toDouble();
        btScalar boneLength = boneMap.value("length").toDouble();

        btScalar endFixRadius = boneMap.value("endFix").toMap().value("radius").toDouble();

        // Yaw & Roll (local)
        QVariantMap localRotationMap = boneMap.value("localRotation").toMap();
        btScalar yAxisRot = localRotationMap.value("y").toDouble();
        btScalar zAxisRot = localRotationMap.value("z").toDouble();

        // Limits
        btVector3 lowerLimits, upperLimits;
        QVariantMap lowerLimitsMap = boneMap.value("lowerLimits").toMap();
        QVariantMap upperLimitsMap = boneMap.value("upperLimits").toMap();

        lowerLimits.setValue(lowerLimitsMap.value("x").toDouble(),
                             lowerLimitsMap.value("y").toDouble(),
                             lowerLimitsMap.value("z").toDouble());
        upperLimits.setValue(upperLimitsMap.value("x").toDouble(),
                             upperLimitsMap.value("y").toDouble(),
                             upperLimitsMap.value("z").toDouble());

        Bone *bone = parent->addBone(yAxisRot,zAxisRot,boneRadius,boneLength,endFixRadius,lowerLimits,upperLimits);
        bone->setMotorModifierData(boneMap["muscle"]);


        // Get the correct ref
        while(ref && ref->getRef()) {
            ref = ref->getRef();
        }
        // Set a back replication
        bone->setRef(ref);
        if(ref)
            ref->addReferee(bone);
        // Set the modifier in case of modification
        bone->setModifiers(modifiers);


        // Add bone recurcively
        return GenomeBuilder::buildFix(shapesFactory, bone->getEndFixation(), modifiers, boneMap.value("endFix"), ref);
    }

    Fixation*  GenomeBuilder::buildFix( btShapesFactory* shapesFactory, Fixation *fix,
                                       QList<GenomeModifier*> modifiers, QVariant fixGenotype, Bone* ref) {

        // We apply the actual modifiers to this genome element
        foreach(GenomeModifier* modifier, modifiers)
            fixGenotype = modifier->modify(fixGenotype);

        // -------------
        // -- sensors --
        // -------------
        foreach(QVariant sensorData, fixGenotype.toMap()["sensors"].toList()) {
           QVariantMap sensorMap = sensorData.toMap();
           switch((SensorType)sensorMap["type"].toInt()) {
           case accelerometerSensor: {
               fix->addSensor(new AccelerometerSensor(sensorData, fix));
           }
               break;
           case gyroscopicSensor: {

               fix->addSensor(new GyroscopicSensor(sensorData, fix));
           }
               break;
           case positionSensor:{
               Fixation* referent = fix;
               if(fix->getParentBone() && fix->getParentBone()->getParentFixation()) {
                   referent = fix->getParentBone()->getParentFixation();
               }
               fix->addSensor(new PositionSensor(sensorData, fix->getEntity()->getShape()->getRoot(), fix));
           }
               break;
           case contactSensor:{

               fix->addSensor(new ContactSensor(sensorData, fix));
           }
               break;
           case boxSmellSensor:{

               fix->addSensor(new BoxSmellSensor(sensorData, fix));

               break;
           }
           case distanceSensor:{

               fix->addSensor(new DistanceSensor(sensorData, fix));
           }
               break;
           }
        }

        // --------------
        // -- effector --
        // --------------
        foreach(QVariant effector, fixGenotype.toMap()["effectors"].toList()) {
           QVariantMap effectorMap = effector.toMap();
           switch((EffectorType)effectorMap["type"].toInt()) {

           case rotationalMotorEffector: break;
           case gripperEffector: {
               fix->addEffector(new GripperEffector(effectorMap, fix));
           }
               break;
           case flyingEffector:{
               fix->addEffector(new FlyingEffector(effectorMap, fix));
           }
               break;
           }
        }

        // -----------
        // -- bones --
        // -----------
        QVariantList bonesVariantList = fixGenotype.toMap().value("bones").toList();

        Bone* correctRef = NULL;
        int i = 0;
        foreach(QVariant bone, bonesVariantList)
        {
            if(ref)
                correctRef = ref->getEndFixation()->getBones()[i];

            GenomeBuilder::buildElement(shapesFactory, fix, modifiers, bone, correctRef);
            i++;
        }

        return fix;
    }

    Fixation* GenomeBuilder::buildRoot(btShapesFactory* shapesFactory, QVariant genotype,
                                       btTransform initPos) {
        // Get the data
        QVariantMap treeShapeMap = genotype.toMap();
        QVariantMap rootFixMap = treeShapeMap.value("rootFix").toMap();
        // Construct the fixation
        return new Fixation(shapesFactory, rootFixMap.value("radius").toDouble(), initPos);
    }

}
