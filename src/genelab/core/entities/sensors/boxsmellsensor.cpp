#include "boxsmellsensor.h"

#include <QVariant>

#define RADIUS_OF_SMELL 20.0

namespace GeneLabCore {

BoxSmellSensor::BoxSmellSensor(Fixation *fixation) :
    SmellSensor(fixation, QString("Box smell sensor"), boxSmellSensor, RigidBodyOrigin::BASIC_SHAPE, RADIUS_OF_SMELL)
{
}

// To create from serialization data
BoxSmellSensor::BoxSmellSensor(QVariant data, Fixation * fixation) :
    SmellSensor(data, RigidBodyOrigin::BASIC_SHAPE, fixation)
{
}

QVariant BoxSmellSensor::generateEmpty()
{
    return SmellSensor::generateEmpty("Box smell sensor", boxSmellSensor, RADIUS_OF_SMELL);
}

}
