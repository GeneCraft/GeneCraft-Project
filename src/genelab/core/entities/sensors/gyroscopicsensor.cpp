#include "gyroscopicsensor.h"

#include "brainin.h"
#include "fixation.h"
#include <QDebug>

namespace GeneLabCore {

GyroscopicSensor::GyroscopicSensor(Fixation *fixation) : Sensor(fixation)
{
    typeName = "Gyroscopic sensor";

    inputYaw = new BrainIn(-M_PI, M_PI);
    inputPitch = new BrainIn(-M_PI,M_PI);
    inputRoll = new BrainIn(-M_PI,M_PI);

    brainInputs.append(inputYaw);
    brainInputs.append(inputPitch);
    brainInputs.append(inputRoll);
}

void GyroscopicSensor::step()
{
    btScalar yaw, pitch, roll;
    fixation->getRigidBody()->getWorldTransform().getBasis().getEulerZYX(yaw, pitch, roll);

    //qDebug() << "GyroscopicSensor::step() yaw = " << yaw << " pitch = " << pitch << " roll = " << roll;

    inputYaw->setValue(yaw);
    inputPitch->setValue(pitch);
    inputRoll->setValue(roll);
}

}
