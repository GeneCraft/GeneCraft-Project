#include "accelerometersensor.h"

#include "brainin.h"
#include "fixation.h"
#include <QDebug>

namespace GeneLabCore {
AccelerometerSensor::AccelerometerSensor(long stepTime, Fixation *fixation) : Sensor(fixation), stepTime(stepTime)
{
    typeName = "Accelerometer sensor";

    inputX = new BrainIn(-3.0,3.0);
    inputY = new BrainIn(-3.0,3.0);
    inputZ = new BrainIn(-3.0,3.0);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);

    // initial position and speed
    oldPosition = fixation->getRigidBody()->getWorldTransform().getOrigin();
    oldSpeed    = btVector3(0,0,0);
}

void AccelerometerSensor::step()
{
    btVector3 position = fixation->getRigidBody()->getWorldTransform().getOrigin();
    btVector3 speed = (position - oldPosition) * stepTime;
    btVector3 acceleration = speed - oldSpeed;
    oldPosition = position;
    oldSpeed    = speed;

    //qDebug() << "AccelerometerSensor::step() x = " << acceleration.x() << " y = " << acceleration.y() << " z = " << acceleration.z();

    inputX->setValue(acceleration.x());
    inputY->setValue(acceleration.y());
    inputZ->setValue(acceleration.z());
}
}
