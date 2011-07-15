#include "floatmutation.h"
#include "tools.h"

#include <QVariant>
#include <QVariantMap>
#include <QDebug>

namespace GeneLabCore {

    FloatMutation::FloatMutation(QVariant variant)
    {
        QVariantMap map = variant.toMap();

        if(map["type"].toInt() == FloatMutationType) {
            probability = map["probability"].toDouble();
            minFact     = map["minFact"].toDouble();
            maxFact     = map["maxFact"].toDouble();
            minValue    = map["minValue"].toDouble();
            maxValue    = map["maxValue"].toDouble();
            enable      = map["enable"].toBool();
        }
        else {
            qDebug() << map;
            qDebug() << Q_FUNC_INFO << "Wrong mutation type" << map["type"].toInt();
        }
    }

    FloatMutation::FloatMutation()
    {
        probability = 1.0;
        minFact     = -1.0;
        maxFact     = 1.0;
        minValue    = 0.0;
        maxValue    = 1.0;
        enable      = true;
    }

    QVariant FloatMutation::serialize(){

        QVariantMap map;

        map.insert("type",QVariant(FloatMutationType));
        map.insert("probability",QVariant((double)probability));
        map.insert("minFact",QVariant((double)minFact));
        map.insert("maxFact",QVariant((double)maxFact));
        map.insert("minValue",QVariant((double)minValue));
        map.insert("maxValue",QVariant((double)maxValue));
        map.insert("enable",QVariant(enable));

        return map;
    }

    void FloatMutation::mutate(QVariantMap &map, QString key){

        float newValue = this->mutate(map.value(key).toDouble());
        map.insert(key,QVariant((double)newValue));

    }

    float FloatMutation::mutate(float value) {

        // mutation ?
        if(canMutate()) {
            return value;
        }

        //float newValue = value + Tools::random(minFact, maxFact) * value;
        float newValue = value + (maxValue - minValue) * Tools::random(minFact, maxFact);

        if(newValue < minValue)
            newValue = minValue;

        if(newValue > maxValue)
            newValue = maxValue;

        return newValue;
    }
}
