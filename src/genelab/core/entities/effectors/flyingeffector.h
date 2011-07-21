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

    // To create
    FlyingEffector(Fixation *fixation);

    // To create from data
    FlyingEffector(QVariant data, Fixation *fixation);

    // To update world.
    void step();

    // To serialize
    QVariant serialize();

private:

    Fixation *fixation;
    BrainOut *impulseX, *impulseY, *impulseZ;
};

}

#endif // FLYINGEFFECTOR_H
