#include "sensor.h"
#include <QVariant>

namespace GeneLabCore {
    Sensor::Sensor(Fixation * fixation, QObject *parent) :
        QObject(parent)
    {
        this->fixation = fixation;
    }


    Sensor::Sensor(QVariant data) {
        this->typeName = data.toMap()["type"].toString();
    }

    QVariant Sensor::serialize() {
        QVariantMap data;
        data.insert("type", this->typeName);
    }

}
