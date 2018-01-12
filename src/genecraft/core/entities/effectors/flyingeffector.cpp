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

#include "flyingeffector.h"

#include "LinearMath/btVector3.h"
#include "body/fixation.h"

#define MASS_FACTOR 0.3f
#define TYPE_NAME "Flying Effector"
#define TYPE flyingEffector

namespace GeneCraftCore {

FlyingEffector::FlyingEffector(Fixation *fixation) : Effector(QString(TYPE_NAME), TYPE), fixation(fixation)
{
    btScalar mass = 1/fixation->getRigidBody()->getInvMass();

    impulseX = new BrainOut(-mass*MASS_FACTOR,mass*MASS_FACTOR);
    impulseY = new BrainOut(-mass*MASS_FACTOR*10.0,mass*MASS_FACTOR*10.0);
    impulseZ = new BrainOut(-mass*MASS_FACTOR,mass*MASS_FACTOR);

    brainOutputs.append(impulseX);
    brainOutputs.append(impulseY);
    brainOutputs.append(impulseZ);
}

FlyingEffector::FlyingEffector(QJsonObject data, Fixation *fixation) : Effector(data), fixation(fixation)
{
    QJsonObject outs = data["outs"].toObject();

    btScalar mass = 1/fixation->getRigidBody()->getInvMass();

    impulseX = new BrainOut(outs["impulseX"].toObject());
    impulseX->setMin(-mass*MASS_FACTOR);
    impulseX->setMin(mass*MASS_FACTOR);

    impulseY = new BrainOut(outs["impulseY"].toObject());
    impulseY->setMin(-mass*MASS_FACTOR*10.0);
    impulseY->setMin(mass*MASS_FACTOR*10.0);

    impulseZ = new BrainOut(outs["impulseZ"].toObject());
    impulseZ->setMin(-mass*MASS_FACTOR);
    impulseZ->setMin(mass*MASS_FACTOR);

    brainOutputs.append(impulseX);
    brainOutputs.append(impulseY);
    brainOutputs.append(impulseZ);
}

void FlyingEffector::step() {

    btVector3 impulse(impulseX->getValue(), impulseY->getValue(), impulseZ->getValue());

    fixation->getRigidBody()->applyCentralImpulse(impulse);
}

QJsonObject FlyingEffector::serialize() {

    QJsonObject data = Effector::serialize();

    QJsonObject bOuts;
    bOuts.insert("impulseX", impulseX->serialize());
    bOuts.insert("impulseY", impulseY->serialize());
    bOuts.insert("impulseZ", impulseZ->serialize());
    data.insert("outs", bOuts);

    return data;
}

QJsonObject FlyingEffector::generateEmpty()
{
    QJsonObject data = Effector::generateEmpty(TYPE_NAME, TYPE);

    // min & max init in contructor according mass of fixation
    BrainOut impulseX(0,0);
    BrainOut impulseY(0,0);
    BrainOut impulseZ(0,0);

    QJsonObject bOuts;
    bOuts.insert("impulseX", impulseX.serialize());
    bOuts.insert("impulseY", impulseY.serialize());
    bOuts.insert("impulseZ", impulseZ.serialize());
    data.insert("outs", bOuts);

    return data;
}

}
