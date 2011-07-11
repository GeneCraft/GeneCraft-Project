#include "bonelimitsmutation.h"

#include "tools.h"
#include <QDebug>

namespace GeneLabCore {

BoneLimitsMutation::BoneLimitsMutation()
{
    axisMutation = new FloatMutation();
}

void BoneLimitsMutation::mutate(QVariantMap &lowerLimits, QVariantMap &upperLimits)
{
    // limits mutation ?
    if(Tools::random(0.f,1.f) <= probability) {

        // foreach axis...
        QString allAxis[] = {"x","y","z"};
        for(int i=0;i<3;i++){

            // y axis created anarchy !
            if(i == 1)
                continue;

            // axis mutation ?
            if(Tools::random(0.f,1.f) <= axisMutation->probability) {

                QString axis = allAxis[i];
                float loValue = lowerLimits[axis].toDouble();
                float upValue = upperLimits[axis].toDouble();

                do
                {
                    loValue = axisMutation->mutate(loValue);
                    upValue = axisMutation->mutate(upValue);
                }
                while(loValue > upValue); // lower value must be lower than the upper value

                lowerLimits.insert(axis,QVariant((double)loValue));
                upperLimits.insert(axis,QVariant((double)upValue));
            }
        }
    }
}

}
