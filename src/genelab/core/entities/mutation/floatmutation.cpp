#include "floatmutation.h"
#include "tools.h"

namespace GeneLabCore {
    void FloatMutation::mutate(QVariantMap &map, QString key){

        // mutation ?
        if(Tools::random(0.f,1.f) <= probability) {

            float factor = Tools::random(minFact, maxFact);
            float newValue = map.value(key).toDouble() + factor * map.value(key).toDouble();

            if(newValue < minValue)
                newValue = minValue;

            if(newValue > maxValue)
                newValue = maxValue;

            map.insert(key,QVariant((double)newValue));
        }
    }
}
