#include "bonelimitsmutation.h"

#include "tools.h"
#include <cmath>
#include <QDebug>

namespace GeneLabCore {

BoneLimitsMutation::BoneLimitsMutation()
{
    axisMutation = new FloatMutation();
    axisMutation->probability    = 0.1;
    axisMutation->minFact        = -0.1;
    axisMutation->maxFact        =  0.1;
    axisMutation->minValue       = -M_PI;
    axisMutation->maxValue       =  M_PI;
}

void BoneLimitsMutation::mutate(QVariantMap &lowerLimits, QVariantMap &upperLimits)
{
    // foreach axis...
    QString allAxis[] = {"x","y","z"};
    for(int i=0;i<3;i++){

        QString axis = allAxis[i];
        float loValue = lowerLimits[axis].toDouble();
        float upValue = upperLimits[axis].toDouble();

        loValue = axisMutation->mutate(loValue);
        upValue = axisMutation->mutate(upValue);

        // Y axis limited between -M_PI/2..M_PI/2
        if(axis == "y") {
            if(loValue < -M_PI_2+0.1)
                loValue = -M_PI_2+0.1;

            if(upValue > M_PI_2-0.1)
                upValue = M_PI_2-0.1;
        }

        // 0 must be included between lo and up
        if(loValue > 0)
            loValue = 0;

        if(upValue < 0)
            upValue = 0;

        lowerLimits.insert(axis,QVariant((double)loValue));
        upperLimits.insert(axis,QVariant((double)upValue));
    }
}

}
