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
    axisMutation->minValue       = -SIMD_PI;
    axisMutation->maxValue       =  SIMD_PI;
}

void BoneLimitsMutation::mutate(QVariantMap &lowerLimits, QVariantMap &upperLimits)
{
    // foreach axis...
    QString allAxis[] = {"x","y","z"};
    for(int i=0;i<3;i++){

        QString axis = allAxis[i];
        btScalar loValue = lowerLimits[axis].toDouble();
        btScalar upValue = upperLimits[axis].toDouble();

        loValue = axisMutation->mutate(loValue);
        upValue = axisMutation->mutate(upValue);

        // Y axis limited between -SIMD_PI/2..SIMD_PI/2
        if(axis == "y") {
            if(loValue < -SIMD_HALF_PI+0.1)
                loValue = -SIMD_HALF_PI+0.1;

            if(upValue > SIMD_HALF_PI-0.1)
                upValue = SIMD_HALF_PI-0.1;
        }

        // 0 must be included between lo and up
        if(loValue > 0)
            loValue = 0;

        if(upValue < 0)
            upValue = 0;

        lowerLimits.remove(axis);
        upperLimits.remove(axis);
        lowerLimits.insert(axis,QVariant((double)loValue));
        upperLimits.insert(axis,QVariant((double)upValue));
    }
}

}
