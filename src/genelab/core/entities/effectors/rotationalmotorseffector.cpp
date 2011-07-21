#include "rotationalmotorseffector.h"

#include <QDebug>
#include <QVariant>
#include <QList>
#include <QVariantList>
#include <QVariantMap>
#include "tools.h"
#include "brain/sinusin.h"

namespace GeneLabCore {

#define TYPE_NAME "Rotational Motor"
#define TYPE rotationalMotorEffector

RotationalMotorsEffector::RotationalMotorsEffector(Bone * bone, btGeneric6DofConstraint *constraint) :  Effector(TYPE_NAME, TYPE),
    constraint(constraint), m_isDisable(false), outputsFrom(0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/)
{
    this->bone = bone;

    // Stabilisation properties
    normalPositionMaxError = 0.001;
    normalPositionFactor   = 10.0;

    for(int i=0;i<3;i++)

        // motor effector only if axis motor is not rigid (has liberty degrees)
        if(constraint->getRotationalLimitMotor(i)->m_loLimit != constraint->getRotationalLimitMotor(i)->m_hiLimit) {

            brainMotorOutputs[i] = new BrainOutMotor(constraint->getRotationalLimitMotor(i));
            brainMotorOutputs[i]->motor->m_enableMotor = true;
            brainMotorOutputs[i]->motor->m_currentPosition = 0;
            this->outputsFrom = 1;
            this->brainOutputs.append(brainMotorOutputs[i]->boMaxMotorForce);
            this->brainOutputs.append(brainMotorOutputs[i]->boTargetVelocity);
        }
        else
            brainMotorOutputs[i] = NULL;

    for(int i = 0; i < 2; i++) {
        this->sinusIn[i] = new SinusIn();
    }
}


RotationalMotorsEffector::RotationalMotorsEffector(QVariant data, Bone *bone, btGeneric6DofConstraint* ct) : Effector(data),
    constraint(ct), m_isDisable(false), outputsFrom(0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/)
{
    this->bone = bone;
    QVariantMap outsMap = data.toMap()["outs"].toMap();

    QString motors[] = {"x","y","z"};

    // Stabilisation properties
    normalPositionMaxError = 0.001;
    normalPositionFactor   = 10.0;

    for(int i = 0; i < 3; i++) {

        QString key = motors[i];
        if(outsMap.contains(key)) {
            brainMotorOutputs[i] = new BrainOutMotor(outsMap.value(key), constraint->getRotationalLimitMotor(i));
            brainMotorOutputs[i]->motor->m_enableMotor = true;
            brainMotorOutputs[i]->motor->m_currentPosition = 0;
            this->outputsFrom = 1;
            this->brainOutputs.append(brainMotorOutputs[i]->boMaxMotorForce);
            this->brainOutputs.append(brainMotorOutputs[i]->boTargetVelocity);
        }
        else
            brainMotorOutputs[i] = NULL;
    }

    for(int i = 0; i < 2; i++) {
        this->sinusIn[i] = new SinusIn();
    }
}

RotationalMotorsEffector::~RotationalMotorsEffector() {

    // delete brain outs
    for(int i=0; i < 3;++i)
        disconnectMotor(i);

    // delete sinus in
    delete this->sinusIn[0];
    delete this->sinusIn[1];
}


void RotationalMotorsEffector::connectMotor(int i)
{
    if(!brainMotorOutputs[i])
    {
        brainMotorOutputs[i] = new BrainOutMotor(constraint->getRotationalLimitMotor(i));
        brainMotorOutputs[i]->motor->m_enableMotor = true;
        brainMotorOutputs[i]->motor->m_currentPosition = 0;
        this->outputsFrom = 1;
        this->brainOutputs.append(brainMotorOutputs[i]->boMaxMotorForce);
        this->brainOutputs.append(brainMotorOutputs[i]->boTargetVelocity);
    }
}

// used to disconnect from brain
void RotationalMotorsEffector::disconnectMotor(int i)
{
    BrainOutMotor * boMotor = brainMotorOutputs[i];

    if(boMotor)
    {
        // delete brain outs
        this->brainOutputs.removeAll(boMotor->boMaxMotorForce);
        this->brainOutputs.removeAll(boMotor->boTargetVelocity);
        delete boMotor->boMaxMotorForce;
        delete boMotor->boTargetVelocity;
        boMotor->boMaxMotorForce = NULL;
        boMotor->boTargetVelocity = NULL;

        // delete brain outs motor
        delete boMotor;
        brainMotorOutputs[i] = NULL;
    }
}

QVariant RotationalMotorsEffector::serialize() {
    QVariantMap data = Effector::serialize().toMap();
    QVariantMap bOuts;
    QString motors[] = {"x","y","z"};
    for(int i = 0; i < 3; i++)
        if(brainMotorOutputs[i]) {
            bOuts.insert(motors[i],brainMotorOutputs[i]->serialize());
        }
    data.insert("outs", bOuts);

    return data;
}

void RotationalMotorsEffector::setOutputsFrom(int outputsFrom)
{
    m_isDisable = false;
    this->outputsFrom = outputsFrom; // from random

    switch(outputsFrom)
    {
    case 1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/:  // brain

        // enable motors
        // enable motors
        for(int i=0;i<3;i++)
            if(brainMotorOutputs[i]){
                btRotationalLimitMotor * motor = brainMotorOutputs[i]->motor;
                motor->m_enableMotor = true;
                motor->m_maxMotorForce = 20.0;
                motor->m_targetVelocity = 0;
                motor->m_currentPosition = 0;
            }


        break;

    case 2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/: // random

        // enable motors
        for(int i=0;i<3;i++)
            if(brainMotorOutputs[i]){
                btRotationalLimitMotor * motor = brainMotorOutputs[i]->motor;
                motor->m_enableMotor = true;
                motor->m_maxMotorForce = 20.0;
                motor->m_targetVelocity = 0;
                motor->m_currentPosition = 0;
            }

        break;

    case 0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/: // normal position

        for(int i=0;i<3;i++)
            if(brainMotorOutputs[i]){
                btRotationalLimitMotor * motor = brainMotorOutputs[i]->motor;
                motor->m_enableMotor = true;
                motor->m_maxMotorForce = 20.0;
                motor->m_targetVelocity = 0;
                motor->m_currentPosition = 0;
            }
        break;
    }
}

void RotationalMotorsEffector::step()
{
    if(!m_isDisable)
    {
        switch(outputsFrom)
        {
        case 1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/:  // brain

            for(int i=0;i<3;i++)
                if(brainMotorOutputs[i])
                    brainMotorOutputs[i]->update();

            break;

        case 2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/: // random

            for(int i=0;i<3;i++)
                if(brainMotorOutputs[i]){
                    btRotationalLimitMotor * motor = brainMotorOutputs[i]->motor;
                    motor->m_maxMotorForce = ( sinusIn[1]->getValue())*10 + 10;
                    motor->m_targetVelocity = (sinusIn[0]->getValue())*5;
                }

            break;

        case 0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/: // normal position

            for(int i=0;i<3;i++)
                if(brainMotorOutputs[i]) {
                    // Stabilisation
                    btRotationalLimitMotor * motor = brainMotorOutputs[i]->motor;
                    if(motor->m_currentPosition < normalPositionMaxError
                       || motor->m_currentPosition > normalPositionMaxError)
                        motor->m_targetVelocity = -normalPositionFactor * motor->m_currentPosition;
                }

            break;

        }
    }
}

void RotationalMotorsEffector::disable()
{
    m_isDisable = true;

    for(int i=0;i<3;i++)
        if(brainMotorOutputs[i]) {
            btRotationalLimitMotor * motor = brainMotorOutputs[i]->motor;
            motor->m_enableMotor = false;
        }
}

}
