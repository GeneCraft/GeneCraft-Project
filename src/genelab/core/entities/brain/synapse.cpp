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
            btScalar x = v.toMap()["x"].toDouble();
            btScalar y = v.toMap()["y"].toDouble();
            btScalar w = v.toMap()["w"].toDouble();
            btScalar distance = 0.0f;
            if(v.toMap().contains("d"))
                distance = v.toMap()["d"].toDouble();
            else
                distance = Tools::random(0.0, 0.2);

            this->connectTo(x, y, distance, w);
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
            dataC.insert("d", (double)c.distance);
            l.append(dataC);
        }

        return l;
    }
}
