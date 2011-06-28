#include "synapse.h"
#include <QVariant>

namespace GeneLabCore {

    Synapse::Synapse(QObject *parent) :
        QObject(parent)
    {
    }

    Synapse::Synapse(QVariant data) {

        QVariantList l = data.toList();

        foreach(QVariant v, l) {
            float x = v.toMap()["x"].toDouble();
            float y = v.toMap()["y"].toDouble();
            float w = v.toMap()["w"].toDouble();
            this->connectTo(x, y, w);
        }
    }

    QVariant Synapse::serialize() {

        QVariantList l;
        for(int i = 0; i < this->connexions.size(); i++) {
            NeuralConnexion c = connexions[i];
            QVariantMap dataC;
            dataC.insert("x", (double)c.x);
            dataC.insert("y", (double)c.y);
            dataC.insert("w", (double)c.weight);
            l.append(dataC);
        }

        return l;
    }
}
