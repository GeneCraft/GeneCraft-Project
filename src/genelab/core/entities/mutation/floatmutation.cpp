#include "floatmutation.h"
#include "tools.h"

namespace GeneLabCore {
    void FloatMutation::mutate(QVariantMap &map, QString key){

        float newValue = this->mutate(map.value(key).toDouble());
        map.insert(key,QVariant((double)newValue));

    }

    float FloatMutation::mutate(float value) {

        // mutation ?
        if(Tools::random(0.f,1.f) > probability) {
            return value;
        }

        float factor = Tools::random(minFact, maxFact);
        float newValue = value + factor * value;

        if(newValue < minValue)
            newValue = minValue;

        if(newValue > maxValue)
            newValue = maxValue;

        return newValue;
    }
}
