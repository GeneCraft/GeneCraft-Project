#include "accelerometersensor.h"

#include "brainin.h"
#include "fixation.h"
#include <QDebug>
#include <QVariant>

namespace GeneLabCore {
AccelerometerSensor::AccelerometerSensor(long stepTime, Fixation *fixation) : Sensor(fixation), stepTime(stepTime)
{
    typeName = "Accelerometer sensor";
    type = accelerometer;

    inputX = new BrainIn(-10.0,10.0);
    inputY = new BrainIn(-10.0,10.0);
    inputZ = new BrainIn(-10.0,10.0);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);

    // initial position and speed
    oldPosition = fixation->getRigidBody()->getWorldTransform().getOrigin();
    oldSpeed    = btVector3(0,0,0);
}

AccelerometerSensor::AccelerometerSensor(QVariant data, Fixation * fixation) : Sensor(data, fixation) {

    this->stepTime = data.toMap()["step"].toInt();

    inputX = new BrainIn(data.toMap()["inputX"]);
    inputY = new BrainIn(data.toMap()["inputY"]);
    inputZ = new BrainIn(data.toMap()["inputZ"]);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);

    // initial position and speed
    oldPosition = fixation->getRigidBody()->getWorldTransform().getOrigin();
    oldSpeed    = btVector3(0,0,0);
}

QVariant AccelerometerSensor::serialize() {
    QVariantMap data = Sensor::serialize().toMap();

    data.insert("inputX", inputX->serialize());
    data.insert("inputY", inputY->serialize());
    data.insert("inputZ", inputZ->serialize());

    data.insert("step", (int)stepTime);

    return data;
}

void AccelerometerSensor::step()
{
    btVector3 position = fixation->getRigidBody()->getWorldTransform().getOrigin();
    btVector3 speed = (position - oldPosition) * stepTime;
    btVector3 acceleration = speed - oldSpeed;

    float factor  = 0.05;
    /*)
    factor = 0.1
    value = new_value*factor + old_value*(1 - factor)
    old_value = value
      */
    oldPosition.setX( oldPosition.getX()*(1-factor) + position.getX()*factor);
    oldPosition.setY( oldPosition.getY()*(1-factor) + position.getY()*factor);
    oldPosition.setZ( oldPosition.getZ()*(1-factor) + position.getZ()*factor);


    oldSpeed.setX( oldSpeed.getX()*(1-factor) + speed.getX()*factor);
    oldSpeed.setY( oldSpeed.getY()*(1-factor) + speed.getY()*factor);
    oldSpeed.setZ( oldSpeed.getZ()*(1-factor) + speed.getZ()*factor);

    inputX->setValue(acceleration.x());
    inputY->setValue(acceleration.y());
    inputZ->setValue(acceleration.z());
}
}
