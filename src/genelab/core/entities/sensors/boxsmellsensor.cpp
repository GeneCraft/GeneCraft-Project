#include "boxsmellsensor.h"

namespace GeneLabCore {

BoxSmellSensor::BoxSmellSensor(Fixation *fixation) :
    SmellSensor(fixation, QString("Box smell sensor"), boxSmellSensor, RigidBodyOrigin::BASIC_SHAPE, 20.0)
{
}

}
