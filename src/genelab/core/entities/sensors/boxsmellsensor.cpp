#include "boxsmellsensor.h"

#include <QVariant>

namespace GeneLabCore {

BoxSmellSensor::BoxSmellSensor(Fixation *fixation) :
    SmellSensor(fixation, QString("Box smell sensor"), boxSmellSensor, RigidBodyOrigin::BASIC_SHAPE, 20.0)
{
}

// To create from serialization data
BoxSmellSensor::BoxSmellSensor(QVariant data, Fixation * fixation) :
    SmellSensor(data, fixation)
{
}

}
