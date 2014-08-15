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

#include "genericfamily.h"

#include "entity.h"
#include "body/treeshape.h"
#include "body/fixation.h"
#include "body/bone.h"
#include "brain/brainfunctional.h"
#include "tools.h"

#include "sensors/accelerometersensor.h"
#include "sensors/boxsmellsensor.h"
#include "sensors/contactsensor.h"
#include "sensors/distancesensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/positionsensor.h"
#include "sensors/sensor.h"
#include "sensors/smellsensor.h"

#include "effectors/effector.h"
#include "effectors/flyingeffector.h"
#include "effectors/grippereffector.h"
#include "effectors/rotationalmotorseffector.h"

namespace GeneCraftCore {
GenericFamily::GenericFamily()
{
}

Entity *GenericFamily::createEntity(QVariant genotype,
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

        Fixation* root = GenericFamily::createRootFromGenotype(shapesFactory, body.value("shape"), initTransform);
        treeShape->setRoot(root);
        entity->setShape(treeShape);
        GenericFamily::buildFixFromGenotype(shapesFactory, root, root,body.value("shape").toMap().value("rootFix"));
    }


    return entity;
}


Entity *GenericFamily::createVirginEntity(btShapesFactory *shapesFactory,
                                                btScalar rootFixRadius,
                                                const btVector3 &initialPosition)
{
    Entity * entity = new Entity("no name", "no family","generic", 1);
    entity->setBrain(new BrainFunctional());

    TreeShape *shape = new TreeShape(shapesFactory);

    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(initialPosition);

    shape->setRoot(new Fixation(shapesFactory,rootFixRadius,initTransform));
    entity->setShape(shape);

    return entity;
}

Fixation* GenericFamily::createRootFromGenotype(btShapesFactory *shapesFactory, QVariant genotype, btTransform initTransform) {
    QVariantMap treeShapeMap = genotype.toMap();

    // Root fix
    QVariantMap rootFixMap = treeShapeMap.value("rootFix").toMap();

    return new Fixation(shapesFactory, rootFixMap.value("radius").toDouble(), initTransform);

}

void GenericFamily::buildFixFromGenotype(btShapesFactory *shapesFactory, Fixation *fix, Fixation* root, QVariant fixGenotype)
{

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

           fix->addSensor(new PositionSensor(sensorData, root, fix));
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

    foreach(QVariant bone, bonesVariantList)
    {
        QVariantMap boneMap = bone.toMap();

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

        Bone *bone = fix->addBone(yAxisRot,zAxisRot,boneRadius,boneLength,endFixRadius,lowerLimits,upperLimits);
        bone->setMotorModifierData(boneMap["muscle"]);
        // Add bone recurcively
        GenericFamily::buildFixFromGenotype(shapesFactory, bone->getEndFixation(), root, boneMap.value("endFix"));
    }
}
}
