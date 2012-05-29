#ifndef LEGEFFECTOR_H
#define LEGEFFECTOR_H

#include "genecraftcoreclasses.h"
#include "effector.h"
#include "brain/brainout.h"
#include "entities/body/leg.h"

namespace GeneCraftCore {

class LegEffector : public Effector
{
public:
    LegEffector(Leg* leg);

    // To create from data
    LegEffector(Leg* leg, QVariant data);

    // To create empty effector serialization data
    static QVariant generateEmpty();

    // To serialize
    QVariant serialize();

    // To update world.
    void step();

private:

    Leg* leg;
    BrainOut* legOutput;
    int cpt;
    
};
}
#endif // LEGEFFECTOR_H
