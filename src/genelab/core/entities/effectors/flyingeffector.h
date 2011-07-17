#ifndef FLYINGEFFECTOR_H
#define FLYINGEFFECTOR_H

#include "genelabcoreclasses.h"
#include "effector.h"
#include "brain/brainout.h"
#include "LinearMath/btScalar.h"

namespace GeneLabCore {

class FlyingEffector : public Effector
{
public:
    FlyingEffector(Fixation *fixation, btScalar maxAltitude = 20.0);

    // To update world.
    void step();

private:

    btScalar maxAltitude;
    Fixation *fixation;
    BrainOut *impulseX, *impulseY, *impulseZ;
};

}

#endif // FLYINGEFFECTOR_H
