#ifndef ROTATIONALMOTORS_H
#define ROTATIONALMOTORS_H

#include <QString>
#include "genelabcoreclasses.h"
#include "modifier.h"
#include "brainout.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"

namespace GeneLabCore {

/**
  * Internal class to box motor brain outputs
  */
class BrainOutMotor
{
public:

    BrainOutMotor(btRotationalLimitMotor * motor,
                  float min_MaxMotorForce = 0.0f, float max_MaxMotorForce = 1000.0f,
                  float min_TargetVelocity = -10.0f, float max_TargetVelocity = 10.0f) : motor(motor)
    {
        boMaxMotorForce = new BrainOut(min_MaxMotorForce,max_MaxMotorForce);
        boTargetVelocity = new BrainOut(min_TargetVelocity,max_TargetVelocity);
    }

    void update()
    {
        motor->m_maxMotorForce = boMaxMotorForce->getValue();
        motor->m_targetVelocity = boTargetVelocity->getValue();
    }

    btRotationalLimitMotor * motor;
    BrainOut * boMaxMotorForce;
    BrainOut * boTargetVelocity;
};

class RotationalMotorsModifier : public Modifier
{
public:

    RotationalMotorsModifier(btGeneric6DofConstraint * constraint);
    bool isDisable()        { return m_isDisable; }
    int getOutPutsFrom()    { return outputsFrom; }

//    static const int OUTPUTS_FROM_NORMAL_POSITION;
//    static const int OUTPUTS_FROM_BRAIN;
//    static const int OUTPUTS_FROM_RANDOM;

signals:

public slots:

    void setOutputsFrom(int outputsFrom);
    void disable();
    void step();

private:
    btGeneric6DofConstraint * constraint;

    bool random;
    bool m_isDisable;
    float randomIncr;
    int outputsFrom;

    // Six outputs from brain
    // Two by motors
    BrainOutMotor * brainOutputs[3];
    SinusIn* sinusIn[2];
};

//const int RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION = 0;
//const int RotationalMotorsModifier::OUTPUTS_FROM_BRAIN = 1;
//const int RotationalMotorsModifier::OUTPUTS_FROM_RANDOM = 2;

}

#endif // ROTATIONALMOTORS_H
