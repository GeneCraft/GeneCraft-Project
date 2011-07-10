#include "integermutation.h"
#include "tools.h"

namespace GeneLabCore {
    void IntegerMutation::mutate(QVariantMap &map, QString key){

        // mutation ?
        if(Tools::random(0.f,1.f) <= probability) {

            float factor = Tools::random(minFact, maxFact);
            int newValue = factor * map.value(key).toInt();

            if(newValue < minValue)
                newValue = minValue;

            if(newValue > maxValue)
                newValue = maxValue;

            map.insert(key,QVariant((int)newValue));
        }
    }
}
