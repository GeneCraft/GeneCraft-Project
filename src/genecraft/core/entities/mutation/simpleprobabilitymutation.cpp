#include "simpleprobabilitymutation.h"

#include <QDebug>
#include <QVariantMap>

namespace GeneCraftCore {

SimpleProbabilityMutation::SimpleProbabilityMutation(){
    probability = 1.0;
    enable      = true;
}

SimpleProbabilityMutation::SimpleProbabilityMutation(QVariant variant){
    QVariantMap map = variant.toMap();

    if(map["type"].toInt() == SimpleProbabilityType) {
        probability = map["probability"].toDouble();
        enable      = map["enable"].toBool();
    }
    else
        qDebug() << Q_FUNC_INFO << "Wrong mutation type" << map["Type"].toInt();
}

QVariant SimpleProbabilityMutation::serialize(){

    QVariantMap map;

    map.insert("type",QVariant(SimpleProbabilityType));
    map.insert("probability",QVariant((double)probability));
    map.insert("enable",QVariant(enable));

    return map;
}

}
