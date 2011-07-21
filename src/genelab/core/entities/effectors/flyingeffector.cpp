#include "flyingeffector.h"

#include "LinearMath/btVector3.h"
#include "body/fixation.h"

#define MASS_FACTOR 0.3f
#define TYPE_NAME "Flying Effector"
#define TYPE flyingEffector

namespace GeneLabCore {

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

FlyingEffector::FlyingEffector(QVariant data, Fixation *fixation) : Effector(data), fixation(fixation)
{
    QVariantMap outs = data.toMap()["outs"].toMap();

    impulseX = new BrainOut(outs["impulseX"]);
    impulseY = new BrainOut(outs["impulseY"]);
    impulseZ = new BrainOut(outs["impulseX"]);

    brainOutputs.append(impulseX);
    brainOutputs.append(impulseY);
    brainOutputs.append(impulseZ);
}

void FlyingEffector::step() {

    btVector3 impulse(impulseX->getValue(), impulseY->getValue(), impulseZ->getValue());

    fixation->getRigidBody()->applyCentralImpulse(impulse);
}

QVariant FlyingEffector::serialize() {

    QVariantMap data = Effector::serialize().toMap();

    QVariantMap bOuts;
    bOuts.insert("impulseX", impulseX->serialize());
    bOuts.insert("impulseY", impulseY->serialize());
    bOuts.insert("impulseZ", impulseZ->serialize());
    data.insert("outs", bOuts);

    return data;
}

}
