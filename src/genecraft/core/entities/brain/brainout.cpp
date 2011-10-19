#include "brainout.h"

namespace GeneCraftCore {

    BrainOut::BrainOut(btScalar min, btScalar max, QObject *) :
        min(min), max(max), value((min + max) / 2.0)
    {
        connexionInfo = "";
    }

    BrainOut::BrainOut(QVariant data)  {
        min = data.toMap()["min"].toFloat();
        max = data.toMap()["max"].toFloat();
        connexionInfo = data.toMap()["connexionInfo"].toString();
        value = (min + max) / 2.0;
    }

    QVariant BrainOut::serialize() {
        QVariantMap data;

        data.insert("min", (double)min);
        data.insert("max", (double)max);
        data.insert("connexionInfo", connexionInfo);

        return data;
    }

    /**
      * Get the value, will be "unormalized" with min and max
      */
    btScalar BrainOut::getValue() {
        return value;
    }

    /**
      * Set the normalized value [-1, 1]
      */
    void  BrainOut::setValue(btScalar value) {
        // Un noramlization
        this->value = (value + 1.0f) / 2.0f * (max - min) + min;
        if(this->value > max) {
            this->value = max;
        }
        if(this->value < min) {
            this->value = min;
        }
        emit newValue(this->value);
    }

    void BrainOut::setConnexionInfo(QVariant info) {
        this->connexionInfo = info;
    }

    QVariant BrainOut::getConnexionInfo() {
        return this->connexionInfo;
    }
}
