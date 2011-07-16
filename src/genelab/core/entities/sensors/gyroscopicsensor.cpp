#include "gyroscopicsensor.h"

#include "brain/brainin.h"
#include "body/fixation.h"
#include <QDebug>
#include <QVariant>
#include "tools.h"

namespace GeneLabCore {

GyroscopicSensor::GyroscopicSensor(Fixation *fixation) : Sensor(fixation){
    typeName = "Gyroscopic sensor";
    type = gyroscopicSensor;

    // value beetween -PI..PI
    inputYaw = new BrainIn(-M_PI, M_PI);
    inputPitch = new BrainIn(-M_PI,M_PI);
    inputRoll = new BrainIn(-M_PI,M_PI);

    brainInputs.append(inputYaw);
    brainInputs.append(inputPitch);
    brainInputs.append(inputRoll);
}

GyroscopicSensor::GyroscopicSensor(QVariant data, Fixation* fixation) : Sensor(data, fixation) {

    inputYaw = new BrainIn(data.toMap()["inputYaw"]);
    inputPitch = new BrainIn(data.toMap()["inputPitch"]);
    inputRoll = new BrainIn(data.toMap()["inputRoll"]);

    brainInputs.append(inputYaw);
    brainInputs.append(inputPitch);
    brainInputs.append(inputRoll);
}

QVariant GyroscopicSensor::serialize() {
    QVariantMap data = Sensor::serialize().toMap();
    data.insert("inputYaw", inputYaw->serialize());
    data.insert("inputPitch", inputPitch->serialize());
    data.insert("inputRoll", inputRoll->serialize());

    return data;
}

QVariant GyroscopicSensor::generateEmpty()
{
    QVariantMap data = Sensor::generateEmpty("Gyroscopic sensor", gyroscopicSensor).toMap();

    BrainIn inputYaw(-M_PI, M_PI);
    BrainIn inputPitch(-M_PI, M_PI);
    BrainIn inputRoll(-M_PI, M_PI);

    inputYaw.connectTo(Tools::random(0.0,1.0),Tools::random(0.0,1.0),Tools::random(-1.0,1.0));
    inputPitch.connectTo(Tools::random(0.0,1.0),Tools::random(0.0,1.0),Tools::random(-1.0,1.0));
    inputRoll.connectTo(Tools::random(0.0,1.0),Tools::random(0.0,1.0),Tools::random(-1.0,1.0));

    data.insert("inputYaw", inputYaw.serialize());
    data.insert("inputPitch", inputPitch.serialize());
    data.insert("inputRoll", inputRoll.serialize());

    return data;
}

void GyroscopicSensor::step(){
    btScalar yaw, pitch, roll;
    fixation->getRigidBody()->getWorldTransform().getBasis().getEulerZYX(yaw, pitch, roll);

    inputYaw->setValue(yaw);
    inputPitch->setValue(pitch);
    inputRoll->setValue(roll);
}

}
