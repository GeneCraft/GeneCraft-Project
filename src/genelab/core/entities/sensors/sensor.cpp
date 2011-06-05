#include "sensor.h"
#include <QVariant>

namespace GeneLabCore {
    Sensor::Sensor(Fixation * fixation, QObject *parent) :
        QObject(parent)
    {
        this->fixation = fixation;
    }


    Sensor::Sensor(QVariant data, Fixation* fixation) {
        this->fixation = fixation;
        this->typeName = data.toMap()["typeName"].toString();
        this->type = (SensorType)data.toMap()["type"].toInt();
    }

    QVariant Sensor::serialize() {
        QVariantMap data;
        data.insert("typeName", this->typeName);
        data.insert("type", (int)this->type);
        return data;
    }

}
