#include "brainin.h"
#include <cstdlib>
#include <QVariant>

namespace GeneLabCore {

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

    QVariant BrainIn::generateEmpty(btScalar min, btScalar max)
    {
        QVariantMap data;

        data.insert("connexions", QVariantList());
        data.insert("min", (double)min);
        data.insert("max", (double)max);

        return data;
    }

}
