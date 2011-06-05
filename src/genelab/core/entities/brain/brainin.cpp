#include "brainin.h"
#include <cstdlib>
#include <QVariant>

namespace GeneLabCore {

    BrainIn::BrainIn(float min, float max, QObject *parent) :
        Synapse(parent), value(0), min(min), max(max)
    {
    }

    BrainIn::BrainIn(QVariant data) : Synapse(data.toMap()["connexions"]), value(0) {
        min = data.toMap()["min"].toFloat();
        max = data.toMap()["max"].toFloat();
    }

    QVariant BrainIn::serialize() {
        QVariantMap data;

        QVariant l = Synapse::serialize();

        data.insert("connexions", l);
        data.insert("min", (double)min);
        data.insert("max", (double)max);

        return data;
    }

}
