#include "flyingeffector.h"

#include "LinearMath/btVector3.h"
#include "body/fixation.h"

#define MASS_FACTOR 0.3f

namespace GeneLabCore {

FlyingEffector::FlyingEffector(Fixation *fixation, btScalar maxAltitude) :
    fixation(fixation), maxAltitude(maxAltitude)
{
    typeName = QString("Flying Effector");
    type     = flyingEffector;

    btScalar mass = 1/fixation->getRigidBody()->getInvMass();

    impulseX = new BrainOut(-mass*MASS_FACTOR,mass*MASS_FACTOR);
    impulseY = new BrainOut(-mass*MASS_FACTOR*10.0,mass*MASS_FACTOR*10.0);
    impulseZ = new BrainOut(-mass*MASS_FACTOR,mass*MASS_FACTOR);

    brainOutputs.append(impulseX);
    brainOutputs.append(impulseY);
    brainOutputs.append(impulseZ);
}

void FlyingEffector::step() {

    btVector3 impulse(impulseX->getValue(), impulseY->getValue(), impulseZ->getValue());

    if(fixation->getRigidBody()->getWorldTransform().getOrigin().y() > maxAltitude)
        impulse.setY(0);

    fixation->getRigidBody()->applyCentralImpulse(impulse);
}

}
