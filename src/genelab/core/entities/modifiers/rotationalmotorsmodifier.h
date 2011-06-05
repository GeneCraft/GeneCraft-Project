#ifndef ROTATIONALMOTORS_H
#define ROTATIONALMOTORS_H

#include <QString>
#include "genelabcoreclasses.h"
#include "modifier.h"
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
        motor->m_maxMotorForce = (boMaxMotorForce->getValue() + boTargetVelocity->getValue())*500;
        motor->m_targetVelocity = (boTargetVelocity->getValue() - boMaxMotorForce->getValue())*10;
    }

    btRotationalLimitMotor * motor;
    BrainOut * boMaxMotorForce;
    BrainOut * boTargetVelocity;
};

class RotationalMotorsModifier : public Modifier
{
public:

    RotationalMotorsModifier(btGeneric6DofConstraint * constraint);
    RotationalMotorsModifier(QVariant data, btGeneric6DofConstraint* ct);
    virtual QVariant serialize();

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
