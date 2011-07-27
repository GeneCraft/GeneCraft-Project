#include "integermutation.h"
#include "tools.h"
#include <QDebug>

namespace GeneLabCore {


    IntegerMutation::IntegerMutation(QVariant variant)
    {
        QVariantMap map = variant.toMap();

        if(map["type"].toInt() == IntegerMutationType) {
            probability = map["probability"].toDouble();
            minIncr     = map["minIncr"].toDouble();
            maxIncr     = map["maxIncr"].toDouble();
            minValue    = map["minValue"].toDouble();
            maxValue    = map["maxValue"].toDouble();
            enable      = map["enable"].toBool();
        }
        else
            qDebug() << Q_FUNC_INFO << "Wrong mutation type" << map["Type"].toInt();
    }

    IntegerMutation::IntegerMutation()
    {
        probability = 1.0;
        minIncr     = -1.0;
        maxIncr     = 1.0;
        minValue     = 0.0;
        maxValue     = 1.0;
        enable       = true;
    }

    QVariant IntegerMutation::serialize(){

        QVariantMap map;

        map.insert("type",QVariant(IntegerMutationType));
        map.insert("probability",QVariant((double)probability));
        map.insert("minIncr",QVariant((double)minIncr));
        map.insert("maxIncr",QVariant((double)maxIncr));
        map.insert("minValue",QVariant((double)minValue));
        map.insert("maxValue",QVariant((double)maxValue));
        map.insert("enable",QVariant(enable));

        return map;
    }

    void IntegerMutation::mutate(QVariantMap &map, QString key){
        int newValue = this->mutate(map.value(key).toInt());
        map.remove(key);
        map.insert(key,QVariant((int)newValue));
    }

    int IntegerMutation::mutate(int value) {

        if(!canMutate()) {
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
