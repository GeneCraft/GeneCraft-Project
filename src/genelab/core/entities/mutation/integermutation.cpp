#include "integermutation.h"
#include "tools.h"
#include <QDebug>

namespace GeneLabCore {
    void IntegerMutation::mutate(QVariantMap &map, QString key){

        // mutation ?
        if(Tools::random(0.f,1.f) <= probability) {

            int factor = Tools::random(minIncr, maxIncr);

            int newValue = map.value(key).toInt() + factor;

            if(newValue < minValue)
                newValue = minValue;

            if(newValue > maxValue)
                newValue = maxValue;

            map.insert(key,QVariant((int)newValue));
        }
    }
}
