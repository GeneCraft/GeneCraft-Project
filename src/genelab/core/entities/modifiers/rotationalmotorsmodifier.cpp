#include "rotationalmotorsmodifier.h"

#include <QDebug>
#include "tools.h"
#include "sinusin.h"

namespace GeneLabCore {
RotationalMotorsModifier::RotationalMotorsModifier(btGeneric6DofConstraint *constraint) : constraint(constraint), random(false)
{

    for(int i=0;i<3;i++)
        brainOutputs[i] = new BrainOutMotor(constraint->getRotationalLimitMotor(i));

    for(int i = 0; i < 2; i++) {
        this->sinusIn[i] = new SinusIn();
    }
}

void RotationalMotorsModifier::setRandom(bool random)
{
    this->random = random;


    ///////////////////////////////////////////// TEST /// DELETEME
    if(random)
        for(int i=0;i<3;i++)
        {
            btRotationalLimitMotor * motor = brainOutputs[i]->motor;
            motor->m_enableMotor = true;

            float minAngularLowerLimit = -3.14;
            float maxAngularLowerLimit = 3.14;

            float minAngularUpperLimit = -3.14;
            float maxAngularUpperLimit = 3.14;

            //motor->m_loLimit = btScalar(Tools::random(-M_PI*0.5,M_PI*0.5));
            //motor->m_hiLimit = btScalar(Tools::random(-M_PI*0.5,M_PI*0.5));
        }
}

void RotationalMotorsModifier::step()
{
    if(random)
    {

        for(int i=0;i<3;i++)
        {
            btRotationalLimitMotor * motor = brainOutputs[i]->motor;
            //motor->m_enableMotor = true;


           motor->m_maxMotorForce = (sinusIn[0]->getValue() + sinusIn[1]->getValue())*100 + 200;
           motor->m_targetVelocity = (sinusIn[0]->getValue() - sinusIn[1]->getValue())*10;
        }
    }
    else
        for(int i=0;i<3;i++)
            brainOutputs[i]->update();
}

}
