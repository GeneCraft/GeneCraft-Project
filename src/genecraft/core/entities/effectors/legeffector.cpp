#include "legeffector.h"

namespace GeneCraftCore {

#define TYPE_NAME "Leg Effector"
#define TYPE legEffector

LegEffector::LegEffector(Leg* leg) : Effector(QString(TYPE_NAME), TYPE)
{
    this->leg = leg;
    legOutput = new BrainOut(-1, 1);
    brainOutputs.append(legOutput);
    cpt = 0;
}

LegEffector::LegEffector(Leg* leg, QVariant data) : Effector(data)
{
    this->leg = leg;
    legOutput = new BrainOut(data.toMap()["legOutput"]);
    brainOutputs.append(legOutput);
}

QVariant LegEffector::generateEmpty()
{
    QVariantMap data = Effector::generateEmpty(TYPE_NAME, TYPE).toMap();

    BrainOut legOutput(-1,1);
    data.insert("legOutput", legOutput.serialize());

    return data;
}

QVariant LegEffector::serialize()
{
    QVariantMap data = Effector::serialize().toMap();
    data.insert("legOutput", legOutput->serialize());
    return data;
}

void LegEffector::step()
{
    cpt ++;
    qDebug() << "CPT : " << cpt;
    if(cpt<10)
        leg->legUp();
    else if(cpt>=10 && cpt < 20)
        leg->legDown();
    else
        cpt=0;

    // Check sensor & actual state, select state



    /*// based on step, set effectors value
    if(legOutput->getValue()>0)
        leg->legUp();
    else if(legOutput->getValue()<0)
        leg->legDown();
    else
        ;//waiting*/
}

}
