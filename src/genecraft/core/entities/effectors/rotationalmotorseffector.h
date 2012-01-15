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

#ifndef ROTATIONALMOTORS_H
#define ROTATIONALMOTORS_H

#include <QString>
#include "genecraftcoreclasses.h"
#include "effector.h"
#include "brainoutmotor.h"

namespace GeneCraftCore {


/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * A rotational motors is an effector to allows entities to move.
 *
 * This effector contains 3 motors (one for each axis). This element is connected to
 * a bone.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class RotationalMotorsEffector : public Effector
{
public:

    RotationalMotorsEffector(Bone * bone, btGeneric6DofConstraint * constraint);
    RotationalMotorsEffector(QVariant data, Bone * bone, btGeneric6DofConstraint* ct);
    ~RotationalMotorsEffector();

    // To connect to brain
    void connectMotor(int i);

    // To disconnect from brain
    void disconnectMotor(int i);

    // To know if the motor is disabled
    bool isDisable()        { return m_isDisable; }

    // To know the origins of motors actions
    int getOutPutsFrom()    { return outputsFrom; }

    // To get bone
    Bone *getBone() { return bone; }

    BrainOutMotor *getBrainOutputs(int i) { return brainMotorOutputs[i]; }

    // To get a seralised representation of effector
    virtual QVariant serialize();

//    static const int OUTPUTS_FROM_NORMAL_POSITION;
//    static const int OUTPUTS_FROM_BRAIN;
//    static const int OUTPUTS_FROM_RANDOM;


    // used to set the origins of motors actions
    void setOutputsFrom(int outputsFrom);

    // used to disable effector
    void disable();

    // used to update motors
    void step();

private:

    // bone
    Bone *bone;

    // origin of motor
    btGeneric6DofConstraint * constraint;

    // effector is active
    bool m_isDisable;

    // motor action define by : random, brain or normal position
    int outputsFrom;

    // used for random outputs
    SinusIn* sinusIn[2];

    // Three motors by muscle (X,Y,Z)
    BrainOutMotor * brainMotorOutputs[3];

    // Stabilisation properties
    btScalar normalPositionMaxError;
    btScalar normalPositionFactor;
};

//const int RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION = 0;
//const int RotationalMotorsModifier::OUTPUTS_FROM_BRAIN = 1;
//const int RotationalMotorsModifier::OUTPUTS_FROM_RANDOM = 2;

}

#endif // ROTATIONALMOTORS_H
