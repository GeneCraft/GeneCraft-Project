#include "grippereffector.h"

#include "body/fixation.h"
#include "btshapesfactory.h"
#include "bullet/btworld.h"

namespace GeneCraftCore {

#define TYPE_NAME "Gripper Effector"
#define TYPE gripperEffector

// To create
GripperEffector::GripperEffector(Fixation *fixation) : Effector(TYPE_NAME, TYPE),
    fixation(fixation)
{
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

QVariant GripperEffector::generateEmpty()
{
    QVariantMap data = Effector::generateEmpty(TYPE_NAME, TYPE).toMap();

    BrainOut gripperOutput(-1,1);
    data.insert("gripperOutput", gripperOutput.serialize());

    return data;
}

}
