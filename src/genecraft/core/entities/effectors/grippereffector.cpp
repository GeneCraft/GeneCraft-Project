/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

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
