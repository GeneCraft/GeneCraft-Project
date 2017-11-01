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

#include <QJsonArray>

namespace GeneCraftCore {
GenericFamily::GenericFamily()
{
}

Entity *GenericFamily::createEntity(QJsonObject genotype,
                                    btShapesFactory *shapesFactory,
                                    const btVector3 &initialPosition)
{

    // Entity & origins
    QJsonObject origins = genotype.value("origins").toObject();
    Entity * entity = new Entity(origins.value("name").toString(),
                                  origins.value("family").toString(),
                                  "generic",
                                  origins.value("generation").toInt());
    // Brain
    entity->setBrain(new BrainFunctional(genotype.value("brain").toObject()));

    // Body
    QJsonObject body = genotype.value("body").toObject();
    if(body.value("shapeType").toString().compare(QString("TreeShape")) == 0)
    {
        TreeShape* treeShape = new TreeShape(shapesFactory);

        btTransform initTransform;
        initTransform.setIdentity();
        initTransform.setOrigin(initialPosition);

        Fixation* root = GenericFamily::createRootFromGenotype(shapesFactory, body.value("shape").toObject(), initTransform);
        treeShape->setRoot(root);
        entity->setShape(treeShape);
        GenericFamily::buildFixFromGenotype(shapesFactory, root, root,body.value("shape").toObject().value("rootFix").toObject());
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

Fixation* GenericFamily::createRootFromGenotype(btShapesFactory *shapesFactory, QJsonObject genotype, btTransform initTransform) {

    // Root fix
    QJsonObject rootFixMap = genotype.value("rootFix").toObject();

    return new Fixation(shapesFactory, rootFixMap.value("radius").toDouble(), initTransform);

}

void GenericFamily::buildFixFromGenotype(btShapesFactory *shapesFactory, Fixation *fix, Fixation* root, QJsonObject fixGenotype)
{

    // -------------
    // -- sensors --
    // -------------
    foreach(QJsonValue sensorData, fixGenotype["sensors"].toArray()) {
       QJsonObject sensorMap = sensorData.toObject();
       switch((SensorType)sensorMap["type"].toInt()) {
       case accelerometerSensor: {
           fix->addSensor(new AccelerometerSensor(sensorData.toObject(), fix));
       }
           break;
       case gyroscopicSensor: {

           fix->addSensor(new GyroscopicSensor(sensorData.toObject(), fix));
       }
           break;
       case positionSensor:{

           fix->addSensor(new PositionSensor(sensorData.toObject(), root, fix));
       }
           break;
       case contactSensor:{

           fix->addSensor(new ContactSensor(sensorData.toObject(), fix));
       }
           break;
       case boxSmellSensor:{

           fix->addSensor(new BoxSmellSensor(sensorData.toObject(), fix));

           break;
       }
       case distanceSensor:{

           fix->addSensor(new DistanceSensor(sensorData.toObject(), fix));
       }
           break;
       }
    }

    // --------------
    // -- effector --
    // --------------
    foreach(QJsonValue effector, fixGenotype["effectors"].toArray()) {
       QJsonObject effectorMap = effector.toObject();
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
    QJsonArray bonesVariantList = fixGenotype.value("bones").toArray();

    foreach(QJsonValue bone, bonesVariantList)
    {
        QJsonObject boneMap = bone.toObject();

        // Radius & lenght
        btScalar boneRadius = boneMap.value("radius").toDouble();
        btScalar boneLength = boneMap.value("length").toDouble();

        btScalar endFixRadius = boneMap.value("endFix").toObject().value("radius").toDouble();

        // Yaw & Roll (local)
        QJsonObject localRotationMap = boneMap.value("localRotation").toObject();
        btScalar yAxisRot = localRotationMap.value("y").toDouble();
        btScalar zAxisRot = localRotationMap.value("z").toDouble();

        // Limits
        btVector3 lowerLimits, upperLimits;
        QJsonObject lowerLimitsMap = boneMap.value("lowerLimits").toObject();
        QJsonObject upperLimitsMap = boneMap.value("upperLimits").toObject();

        lowerLimits.setValue(lowerLimitsMap.value("x").toDouble(),
                             lowerLimitsMap.value("y").toDouble(),
                             lowerLimitsMap.value("z").toDouble());
        upperLimits.setValue(upperLimitsMap.value("x").toDouble(),
                             upperLimitsMap.value("y").toDouble(),
                             upperLimitsMap.value("z").toDouble());

        Bone *b = fix->addBone(yAxisRot,zAxisRot,boneRadius,boneLength,endFixRadius,lowerLimits,upperLimits);
        b->setMotorModifierData(boneMap["muscle"].toObject());
        // Add bone recurcively
        GenericFamily::buildFixFromGenotype(shapesFactory, b->getEndFixation(), root, boneMap.value("endFix").toObject());
    }
}
}
