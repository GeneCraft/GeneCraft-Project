#include "accelerometersensor.h"

#include "brain/brainin.h"
#include "body/fixation.h"
#include <QDebug>
#include <QVariant>
#include "tools.h"

#define MIN_ACCELERATION -1.0
#define MAX_ACCELERATION 1.0


namespace GeneCraftCore {

AccelerometerSensor::AccelerometerSensor(Fixation *fixation) : Sensor(fixation)
{
    typeName = "Accelerometer sensor";
    type = accelerometerSensor;

    inputX = new BrainIn(MIN_ACCELERATION,MAX_ACCELERATION);
    inputY = new BrainIn(MIN_ACCELERATION,MAX_ACCELERATION);
    inputZ = new BrainIn(MIN_ACCELERATION,MAX_ACCELERATION);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);

    // initial position and speed
    oldPosition = fixation->getRigidBody()->getWorldTransform().getOrigin();
    oldSpeed    = btVector3(0,0,0);

    tmpMinAcc = tmpMaxAcc = 0;
}

AccelerometerSensor::AccelerometerSensor(QVariant data, Fixation * fixation) : Sensor(data, fixation) {

    inputX = new BrainIn(data.toMap()["inputX"]);
    inputY = new BrainIn(data.toMap()["inputY"]);
    inputZ = new BrainIn(data.toMap()["inputZ"]);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);

    // initial position and speed
    oldPosition = fixation->getRigidBody()->getWorldTransform().getOrigin();
    oldSpeed    = btVector3(0,0,0);

    tmpMinAcc = tmpMaxAcc = 0;
}

QVariant AccelerometerSensor::generateEmpty()
{
    QVariantMap data = Sensor::generateEmpty("Accelerometer sensor", accelerometerSensor).toMap();

    BrainIn inputX(MIN_ACCELERATION,MAX_ACCELERATION);
    BrainIn inputY(MIN_ACCELERATION,MAX_ACCELERATION);
    BrainIn inputZ(MIN_ACCELERATION,MAX_ACCELERATION);

    inputX.connectRandomly();
    inputY.connectRandomly();
    inputZ.connectRandomly();

    data.insert("inputX", inputX.serialize());
    data.insert("inputY", inputY.serialize());
    data.insert("inputZ", inputZ.serialize());

    return data;
}

QVariant AccelerometerSensor::serialize() {
    QVariantMap data = Sensor::serialize().toMap();

    data.insert("inputX", inputX->serialize());
    data.insert("inputY", inputY->serialize());
    data.insert("inputZ", inputZ->serialize());

    return data;
}

void AccelerometerSensor::step()
{
    btVector3 position = fixation->getRigidBody()->getWorldTransform().getOrigin();
    btVector3 speed = (position - oldPosition);// * stepTime;
    btVector3 acceleration = speed - oldSpeed;

    // btScalar factor  = 0.05;
    btScalar factor  = .1;

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
