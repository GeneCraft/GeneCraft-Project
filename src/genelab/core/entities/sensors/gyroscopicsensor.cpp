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
    inputYaw = new BrainIn(-SIMD_PI, SIMD_PI);
    inputPitch = new BrainIn(-SIMD_PI,SIMD_PI);
    inputRoll = new BrainIn(-SIMD_PI,SIMD_PI);

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

    BrainIn inputYaw(-SIMD_PI, SIMD_PI);
    BrainIn inputPitch(-SIMD_PI, SIMD_PI);
    BrainIn inputRoll(-SIMD_PI, SIMD_PI);

    inputYaw.connectRandomly();
    inputPitch.connectRandomly();
    inputRoll.connectRandomly();

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
