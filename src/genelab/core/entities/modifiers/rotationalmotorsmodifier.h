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
                  float min_MaxMotorForce = 0.0f, float max_MaxMotorForce = 100.0f,
                  float min_TargetVelocity = 0.0f, float max_TargetVelocity = 100.0f) : motor(motor)
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

    void setRandom(bool random);

signals:

public slots:

    void step();

private:
    btGeneric6DofConstraint * constraint;

    bool random;
    float randomIncr;

    // Six outputs from brain
    // Two by motors
    BrainOutMotor * brainOutputs[3];
    SinusIn* sinusIn[2];
};

}

#endif // ROTATIONALMOTORS_H
