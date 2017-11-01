/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gyroscopicsensor.h"

#include "brain/brainin.h"
#include "body/fixation.h"
#include <QDebug>
#include <QVariant>
#include "tools.h"

namespace GeneCraftCore {

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

GyroscopicSensor::GyroscopicSensor(QJsonObject data, Fixation* fixation) : Sensor(data, fixation) {

    inputYaw = new BrainIn(data["inputYaw"].toObject());
    inputPitch = new BrainIn(data["inputPitch"].toObject());
    inputRoll = new BrainIn(data["inputRoll"].toObject());

    brainInputs.append(inputYaw);
    brainInputs.append(inputPitch);
    brainInputs.append(inputRoll);
}

QJsonObject GyroscopicSensor::serialize() {
    QJsonObject data = Sensor::serialize();
    data.insert("inputYaw", inputYaw->serialize());
    data.insert("inputPitch", inputPitch->serialize());
    data.insert("inputRoll", inputRoll->serialize());

    return data;
}

QJsonObject GyroscopicSensor::generateEmpty()
{
    QJsonObject data = Sensor::generateEmpty("Gyroscopic sensor", gyroscopicSensor);

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
