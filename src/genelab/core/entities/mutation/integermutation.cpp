#include "integermutation.h"
#include "tools.h"
#include <QDebug>

namespace GeneLabCore {
    void IntegerMutation::mutate(QVariantMap &map, QString key){
        int newValue = this->mutate(map.value(key).toInt());
        map.insert(key,QVariant((int)newValue));
    }

    int IntegerMutation::mutate(int value) {

        if(Tools::random(0.f,1.f) > probability) {
            return value;
        }

        int factor = Tools::random(minIncr, maxIncr);
        int newValue = value + factor;

        if(newValue < minValue)
            newValue = minValue;

        if(newValue > maxValue)
            newValue = maxValue;

        return newValue;
    }
}
