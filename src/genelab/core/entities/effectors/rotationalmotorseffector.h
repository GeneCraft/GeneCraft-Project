#ifndef ROTATIONALMOTORS_H
#define ROTATIONALMOTORS_H

#include <QString>
#include "genelabcoreclasses.h"
#include "effector.h"
#include "brain/brainout.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"

namespace GeneLabCore {

/**
  * Internal class to box motor brain outputs
  */
class BrainOutMotor
{
public:

    BrainOutMotor(btRotationalLimitMotor * motor,
                  float min_MaxMotorForce = 0.0f, float max_MaxMotorForce = 1.0f,
                  float min_TargetVelocity = 0.0f, float max_TargetVelocity = 1.0f) : motor(motor)
    {
        boMaxMotorForce = new BrainOut(min_MaxMotorForce,max_MaxMotorForce);
        boTargetVelocity = new BrainOut(min_TargetVelocity,max_TargetVelocity);
    }
    ~BrainOutMotor() {
        delete this->boMaxMotorForce;
        delete this->boTargetVelocity;
    }

    BrainOutMotor(QVariant data, btRotationalLimitMotor* motor) : motor(motor){
        QVariantMap outMap = data.toMap();
        QVariantList dataL = outMap["brainOuts"].toList();
        boMaxMotorForce = new BrainOut(dataL[0]);
        boTargetVelocity = new BrainOut(dataL[1]);
    }

    QVariant serialize()  {
        QVariantMap data;
        QVariantList outs;
        outs.append(boMaxMotorForce->serialize());
        outs.append(boTargetVelocity->serialize());
        data.insert("brainOuts", (QVariantList)outs);
        return data;
    }

    void update()
    {
        motor->m_maxMotorForce
                = (boMaxMotorForce->getValue() + boTargetVelocity->getValue())*10;
        motor->m_targetVelocity
                = (boTargetVelocity->getValue() - boMaxMotorForce->getValue())*5;
    }

    btRotationalLimitMotor * motor;
    BrainOut * boMaxMotorForce;
    BrainOut * boTargetVelocity;
};

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

    BrainOutMotor *getBrainOutputs(int i) { return brainOutputs[i]; }

    /**
     * used to get a seralised representation of effector
     * (don't return the state of the motors but only the structure)
     */
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
    BrainOutMotor * brainOutputs[3];

    // Stabilisation properties
    btScalar normalPositionMaxError;
    btScalar normalPositionFactor;
};

//const int RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION = 0;
//const int RotationalMotorsModifier::OUTPUTS_FROM_BRAIN = 1;
//const int RotationalMotorsModifier::OUTPUTS_FROM_RANDOM = 2;

}

#endif // ROTATIONALMOTORS_H
