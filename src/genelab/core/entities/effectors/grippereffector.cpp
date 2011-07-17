#include "grippereffector.h"

#include "body/fixation.h"
#include "factories/btshapesfactory.h"
#include "world/btworld.h"

namespace GeneLabCore {

// To create
GripperEffector::GripperEffector(Fixation *fixation) :
    constraint(NULL), fixation(fixation)
{
    typeName    = QString("Gripper Effector");
    type       = gripperEffector;

    // create the air contraint
    constraint = new btPoint2PointConstraint(*fixation->getRigidBody(),btVector3(0,0,0));
    constraint->setEnabled(false);
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->addConstraint(constraint);

    gripperOutput = new BrainOut(-1,1);
    brainOutputs.append(gripperOutput);
}

// To create from serialization data
GripperEffector::GripperEffector(QVariant data, Fixation * fixation) :
    Effector(data), fixation(fixation) {

    // create the air contraint
    constraint = new btPoint2PointConstraint(*fixation->getRigidBody(),btVector3(0,0,0));
    constraint->setEnabled(false);
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->addConstraint(constraint);

    gripperOutput = new BrainOut(data.toMap()["gripperOutput"]);
    brainOutputs.append(gripperOutput);
}

// Destructor
GripperEffector::~GripperEffector()
{
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->removeConstraint(constraint);
    delete constraint;
}

// To serialize
QVariant GripperEffector::serialize() {
    QVariantMap data = Effector::serialize().toMap();
    data.insert("gripperOutput", gripperOutput->serialize());
    return data;
}

void GripperEffector::step() {

    // disable <= 0 > activate
    if(gripperOutput->getValue() > 0)
    {
        // not already enable
        if(!constraint->isEnabled()) {

            // TODO check if fixation collide with static object...


            // set the new grip origin
            constraint->setPivotB(fixation->getRigidBody()->getWorldTransform().getOrigin());

            // activate the constraint
            constraint->setEnabled(true);
        }
    }
    else
        // disable the contraint
        constraint->setEnabled(false);
}

}
