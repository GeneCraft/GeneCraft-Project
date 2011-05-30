#include "rotationalmotorsmodifier.h"

#include <QDebug>
#include "tools.h"

namespace GeneLabCore {
RotationalMotorsModifier::RotationalMotorsModifier(btGeneric6DofConstraint *constraint) : constraint(constraint), random(false)
{
    randomIncr = Tools::random(-100,100);

    for(int i=0;i<3;i++)
        brainOutputs[i] = new BrainOutMotor(constraint->getRotationalLimitMotor(i));
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

            motor->m_loLimit = btScalar(Tools::random(-M_PI*0.5,M_PI*0.5));
            motor->m_hiLimit = btScalar(Tools::random(-M_PI*0.5,M_PI*0.5));
        }
}

void RotationalMotorsModifier::step()
{
    if(random)
    {
        randomIncr = ++randomIncr % 1000;

        for(int i=0;i<3;i++)
        {
            btRotationalLimitMotor * motor = brainOutputs[i]->motor;
            //motor->m_enableMotor = true;

            motor->m_maxMotorForce = sin(randomIncr) * 1.0;
            motor->m_targetVelocity = sin(randomIncr) * 1.0;
        }
    }
    else
        for(int i=0;i<3;i++)
            brainOutputs[i]->update();
}

}
