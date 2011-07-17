#include "grippereffector.h"

#include "body/fixation.h"
#include "factories/btshapesfactory.h"
#include "world/btworld.h"

namespace GeneLabCore {

GripperEffector::GripperEffector(Fixation *fixation) : constraint(NULL) {

    this->fixation = fixation;
    this->typeName = "Gripper Effector";

    // create the air contraint
    constraint = new btPoint2PointConstraint(*fixation->getRigidBody(),btVector3(0,0,0));
    constraint->setEnabled(false);
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->addConstraint(constraint);

    gripState = new BrainOut(-1,1);
    outs.append(gripState);
}

void GripperEffector::step() {
    // activate or disable
    constraint->setEnabled(gripState->getValue() > 0);
}

}
