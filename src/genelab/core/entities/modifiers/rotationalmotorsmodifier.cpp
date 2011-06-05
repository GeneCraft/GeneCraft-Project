#include "rotationalmotorsmodifier.h"

#include <QDebug>
#include <QVariant>
#include <QList>
#include <QVariantList>
#include <QVariantMap>
#include "tools.h"
#include "sinusin.h"

namespace GeneLabCore {

RotationalMotorsModifier::RotationalMotorsModifier(btGeneric6DofConstraint *constraint) :
    constraint(constraint), random(false), m_isDisable(false), outputsFrom(0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/)
{
    this->typeName = "RotationalMotor";
    for(int i=0;i<3;i++)
    {
        brainOutputs[i] = new BrainOutMotor(constraint->getRotationalLimitMotor(i));
        brainOutputs[i]->motor->m_enableMotor = true;
        brainOutputs[i]->motor->m_currentPosition = 0;
        this->outputsFrom = 1;
        this->outs.append(brainOutputs[i]->boMaxMotorForce);
        this->outs.append(brainOutputs[i]->boTargetVelocity);
    }

    for(int i = 0; i < 2; i++) {
        this->sinusIn[i] = new SinusIn();
    }
}


RotationalMotorsModifier::RotationalMotorsModifier(QVariant data, btGeneric6DofConstraint* ct) : Modifier(data),
    constraint(ct), random(false), m_isDisable(false), outputsFrom(0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/)
{
    QVariantMap outsMap = data.toMap();
    for(int i = 0; i < 3; i++) {
        brainOutputs[i] = new BrainOutMotor(outsMap["outs"].toList()[i], constraint->getRotationalLimitMotor(i));
        brainOutputs[i]->motor->m_enableMotor = true;
        brainOutputs[i]->motor->m_currentPosition = 0;
        this->outputsFrom = 1;
        this->outs.append(brainOutputs[i]->boMaxMotorForce);
        this->outs.append(brainOutputs[i]->boTargetVelocity);
    }


    for(int i = 0; i < 2; i++) {
        this->sinusIn[i] = new SinusIn();
    }
}

QVariant RotationalMotorsModifier::serialize() {
    QVariantMap data = Modifier::serialize().toMap();
    QVariantList bOuts;
    for(int i = 0; i < 3; i++) {
        bOuts.append(brainOutputs[i]->serialize());
    }
    data.insert("outs", bOuts);

    return data;
}

void RotationalMotorsModifier::setOutputsFrom(int outputsFrom)
{
    m_isDisable = false;
    this->outputsFrom = outputsFrom; // from random

    switch(outputsFrom)
    {
    case 1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/:  // brain
        break;

    case 2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/: // random

        for(int i=0;i<3;i++)
        {
            btRotationalLimitMotor * motor = brainOutputs[i]->motor;
            motor->m_enableMotor = true;
        }
        break;

    case 0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/: // normal position

        for(int i=0;i<3;i++)
        {
            btRotationalLimitMotor * motor = brainOutputs[i]->motor;
            motor->m_enableMotor = true;
            motor->m_maxMotorForce = 1000.0;
            motor->m_targetVelocity = 0;
            motor->m_currentPosition = 0;

        }
        break;
    }
}

void RotationalMotorsModifier::step()
{
    if(!m_isDisable)
    {
        switch(outputsFrom)
        {
        case 1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/:  // brain

            for(int i=0;i<3;i++)
                brainOutputs[i]->update();

            break;

        case 2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/: // random

            for(int i=0;i<3;i++)
            {
                btRotationalLimitMotor * motor = brainOutputs[i]->motor;
//                motor->m_maxMotorForce = (sinusIn[0]->getValue() + sinusIn[1]->getValue())*100 + 200;
//                motor->m_targetVelocity = (sinusIn[0]->getValue() - sinusIn[1]->getValue())*10;
                motor->m_maxMotorForce = ( sinusIn[1]->getValue())*400 + 400;
                motor->m_targetVelocity = (sinusIn[0]->getValue())*10;
            }
            break;

        case 0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/: // normal position

            for(int i=0;i<3;i++)
            {
                // Stabilisation
                btRotationalLimitMotor * motor = brainOutputs[i]->motor;
                btScalar max_error = 0.001;
                btScalar factor    = 10.0;

                if(motor->m_currentPosition < max_error || motor->m_currentPosition > max_error)
                    motor->m_targetVelocity = -factor * motor->m_currentPosition;
            }

            break;

        }
    }
}

void RotationalMotorsModifier::disable()
{
    m_isDisable = true;

    for(int i=0;i<3;i++)
    {
        btRotationalLimitMotor * motor = brainOutputs[i]->motor;
        motor->m_enableMotor = false;
    }
}

}
