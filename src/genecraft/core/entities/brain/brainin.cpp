#include "brainin.h"
#include <cstdlib>
#include <QVariant>

namespace GeneCraftCore {

    BrainIn::BrainIn(btScalar min, btScalar max, QObject *parent) :
        Synapse(parent), value(0), min(min), max(max)
    {
    }

    BrainIn::BrainIn(QVariant data) : Synapse(data.toMap()["connexions"]), value(0) {
        min = data.toMap()["min"].toFloat();
        max = data.toMap()["max"].toFloat();
    }

    QVariant BrainIn::serialize() {
        QVariantMap data;

        data.insert("connexions", Synapse::serialize());
        data.insert("min", (double)min);
        data.insert("max", (double)max);

        return data;
    }

    /**
      * Set the normalized value, will be normalized between min and max.
      */
    void BrainIn::setValue(btScalar value) {
        // Normalization (projection in range -1..1)
        this->value = (value - min) / (max - min) * 2.0f - 1.0f;
    }

    /**
      * Get the normalized value [-1, 1]
      */
    btScalar BrainIn::getValue() {
        return this->value;
    }

    QVariant BrainIn::generateEmpty(btScalar min, btScalar max)
    {
        QVariantMap data;

        data.insert("connexions", QVariantList());
        data.insert("min", (double)min);
        data.insert("max", (double)max);

        return data;
    }

}
