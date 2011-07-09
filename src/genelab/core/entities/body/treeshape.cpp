#include "treeshape.h"

#include <QVariant>
#include <QVariantMap>

#include "fixation.h"
#include "treeshape.h"
#include "bone.h"
#include "bullet/bulletengine.h"
#include "btshapesfactory.h"
#include "sensors/sensor.h"
#include "sensors/accelerometersensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/positionsensor.h"
#include "sensors/contactsensor.h"

namespace GeneLabCore {
    TreeShape::TreeShape(btShapesFactory* shapesFactory, QObject *parent) :
        QObject(parent)
    {
        this->shapesFactory = shapesFactory;
        this->root = NULL;
    }


    TreeShape::~TreeShape() {
        delete root;
    }

    void TreeShape::createRootFromGenotype(QVariant genotype, btTransform initTransform) {
        QVariantMap treeShapeMap = genotype.toMap();

        // Root fix
        QVariantMap rootFixMap = treeShapeMap.value("rootFix").toMap();

        root = new Fixation(shapesFactory, rootFixMap.value("radius").toDouble(), initTransform);

    }

    void TreeShape::buildFixFromGenotype(Fixation *fix, QVariant fixGenotype)
    {
        foreach(QVariant sensor, fixGenotype.toMap()["sensors"].toList()) {
           QVariantMap sensorMap = sensor.toMap();
           switch((SensorType)sensorMap["type"].toInt()) {
           case accelerometer: {
               AccelerometerSensor* s = new AccelerometerSensor(sensor, fix);
               fix->addSensor(s);
           }
               break;
           case gyroscopic: {

               GyroscopicSensor* s = new GyroscopicSensor(sensor, fix);
               fix->addSensor(s);
           }
               break;
           case position:{

               PositionSensor* s = new PositionSensor(sensor, this->root, fix);
               fix->addSensor(s);
           }
               break;
           case contact:{

               ContactSensor* s = new ContactSensor(sensor, fix);
               fix->addSensor(s);
           }
               break;
           }
        }

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
            buildFixFromGenotype(bone->getEndFixation(),boneMap.value("endFix"));
        }
    }

    void TreeShape::setRoot(Fixation *root) {
        this->root = root;
    }

    Fixation* TreeShape::getRoot() {
        return this->root;
    }

    void TreeShape::setup() {
        getRoot()->setup();
    }

    QVariant TreeShape::serialize()
    {
        QVariantMap treeShape, shape;

        treeShape.insert("shapeType", QVariant("TreeShape"));
        shape.insert("rootFix", root->serialize());
        treeShape.insert("shape",shape);

        return treeShape;
    }
}
