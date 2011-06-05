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
            int x = v.toMap()["x"].toInt();
            int y = v.toMap()["y"].toInt();
            float w = v.toMap()["w"].toDouble();
            this->connectTo(x, y, w);
        }

    }

    QVariant Synapse::serialize() {

        QVariantList l;
        for(int i = 0; i < this->connexions.size(); i++) {
            NeuralConnexion c = connexions[i];
            QVariantMap dataC;
            dataC.insert("x", c.x);
            dataC.insert("y", c.y);
            dataC.insert("w", (double)c.weight);
            l.append(dataC);
        }

        return l;
    }

}
