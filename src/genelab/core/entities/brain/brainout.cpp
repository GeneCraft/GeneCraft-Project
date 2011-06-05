#include "brainout.h"

namespace GeneLabCore {

    BrainOut::BrainOut(float min, float max, QObject *parent) :
        min(min), max(max), value((min + max) / 2.0)
    {
        connexionInfo = "";
    }

    BrainOut::BrainOut(QVariant data)  {
        min = data.toMap()["min"].toFloat();
        max = data.toMap()["max"].toFloat();
        connexionInfo = data.toMap()["connexionInfo"].toString();
    }

    QVariant BrainOut::serialize() {
        QVariantMap data;

        data.insert("min", (double)min);
        data.insert("max", (double)max);
        data.insert("connexionInfo", connexionInfo);

        return data;
    }

}
