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

#include "BulletDynamics/Dynamics/btRigidBody.h"

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
    //TODO FIX; USE PHYSOBJECT
    /*fixation->getRigidBody()->getWorldTransform().getBasis().getEulerZYX(yaw, pitch, roll);

    inputYaw->setValue(yaw);
    inputPitch->setValue(pitch);
    inputRoll->setValue(roll);
    */
}

}
