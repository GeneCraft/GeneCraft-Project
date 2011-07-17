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

GripperEffector::~GripperEffector()
{
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->removeConstraint(constraint);
    delete constraint;
}

void GripperEffector::step() {

    // disable <= 0 > activate
    if(gripState->getValue() > 0)
    {
        // not already enable
        if(!constraint->isEnabled()) {

            // set the new grip origin
            constraint->setPivotA(btVector3(0,0,0));

            // activate the constraint
            constraint->setEnabled(true);
        }
    }
    else
        // disable the contraint
        constraint->setEnabled(false);
}

}
