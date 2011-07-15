#include "accelerometersensor.h"

#include "brain/brainin.h"
#include "body/fixation.h"
#include <QDebug>
#include <QVariant>
#include "tools.h"

#define MIN_ACCELERATION -1.0
#define MAX_ACCELERATION 1.0


namespace GeneLabCore {

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

    //this->stepTime = data.toMap()["step"].toInt();

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

    BrainIn *inputX = new BrainIn(MIN_ACCELERATION,MAX_ACCELERATION);
    BrainIn *inputY = new BrainIn(MIN_ACCELERATION,MAX_ACCELERATION);
    BrainIn *inputZ = new BrainIn(MIN_ACCELERATION,MAX_ACCELERATION);

    inputX->connectTo(Tools::random(0.0,1.0),Tools::random(0.0,1.0),Tools::random(-1.0,1.0));
    inputY->connectTo(Tools::random(0.0,1.0),Tools::random(0.0,1.0),Tools::random(-1.0,1.0));
    inputZ->connectTo(Tools::random(0.0,1.0),Tools::random(0.0,1.0),Tools::random(-1.0,1.0));

    data.insert("inputX", inputX->serialize());
    data.insert("inputY", inputY->serialize());
    data.insert("inputZ", inputZ->serialize());

    delete inputX;
    delete inputY;
    delete inputZ;

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

    // float factor  = 0.05;
    float factor  = 1.;

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


    if(acceleration.x() < tmpMinAcc)
        tmpMinAcc = acceleration.x();
//    if(acceleration.y() < tmpMinAcc)
//        tmpMinAcc = acceleration.y();
    if(acceleration.z() < tmpMinAcc)
        tmpMinAcc = acceleration.z();

    if(acceleration.x() > tmpMaxAcc)
        tmpMaxAcc = acceleration.x();
//    if(acceleration.y() > tmpMaxAcc)
//        tmpMaxAcc = acceleration.y();
    if(acceleration.z() > tmpMaxAcc)
        tmpMaxAcc = acceleration.z();

    //qDebug() << tmpMinAcc << tmpMaxAcc;

    inputX->setValue(acceleration.x());
    inputY->setValue(acceleration.y());
    inputZ->setValue(acceleration.z());
}
}
