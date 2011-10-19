#ifndef GRIPPEREFFECTOR_H
#define GRIPPEREFFECTOR_H

#include "genecraftcoreclasses.h"
#include "effector.h"
#include "brain/brainout.h"
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"

namespace GeneCraftCore {

class GripperEffector : public Effector
{
public:
    GripperEffector(Fixation *fixation);

    // To create from serialization data
    GripperEffector(QVariant data, Fixation * fixation);

    // To create empty effector serialization data
    static QVariant generateEmpty();

    // Destructor
    ~GripperEffector();

    // To serialize
    QVariant serialize();

    // To update world.
    void step();

private:

    Fixation *fixation;
    btPoint2PointConstraint *constraint;
    BrainOut *gripperOutput;
};

}
#endif // GRIPPEREFFECTOR_H
