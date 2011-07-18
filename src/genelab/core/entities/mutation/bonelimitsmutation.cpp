#include "bonelimitsmutation.h"

#include "tools.h"
#include <cmath>
#include <QDebug>

namespace GeneLabCore {

BoneLimitsMutation::BoneLimitsMutation()
{
    probability                  = 0.1;

    axisMutation = new FloatMutation();
    axisMutation->probability    = -0.1;
    axisMutation->minFact        = -0.01;
    axisMutation->maxFact        =  0.01;
    axisMutation->minValue       = -M_PI+0.01; // -INF (cyclic) ?
    axisMutation->maxValue       =  M_PI-0.01; // +INF (cyclic) ?
}

void BoneLimitsMutation::mutate(QVariantMap &lowerLimits, QVariantMap &upperLimits)
{
    // limits mutation ?
    if(Tools::random(0.f,1.f) <= probability) {

        // foreach axis...
        QString allAxis[] = {"x","y","z"};
        for(int i=0;i<3;i++){

            // axis mutation ?
            if(Tools::random(0.f,1.f) <= axisMutation->probability) {

                QString axis = allAxis[i];
                float loValue = lowerLimits[axis].toDouble();
                float upValue = upperLimits[axis].toDouble();

                // If y axis
                if(axis == "y") {
                    if(loValue < -M_PI/2.+0.1) {
                        loValue = -M_PI/2.+0.1;
                    }
                    if(upValue > M_PI/2.-0.1) {
                        upValue = M_PI/2.-0.1;
                    }
                }

                loValue = axisMutation->mutate(loValue);
                upValue = axisMutation->mutate(upValue);

                // lower value must be lower than the upper value
                if(loValue > upValue) {
                    loValue = upValue;
                }

                lowerLimits.insert(axis,QVariant((double)loValue));
                upperLimits.insert(axis,QVariant((double)upValue));
            }
        }
    }
}

}
