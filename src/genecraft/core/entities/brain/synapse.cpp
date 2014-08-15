/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "synapse.h"
#include <QVariant>

namespace GeneCraftCore {

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


    QList<NeuralConnexion> Synapse::getConnexions() {
        return this->connexions;
    }

    void Synapse::connectRandomly() {
        this->connexions.append(NeuralConnexion(Tools::random(btScalar(0.0),btScalar(1.0)), // X
                                                Tools::random(btScalar(0.0),btScalar(1.0)), // Y
                                                Tools::random(btScalar(0.0),btScalar(0.2)), // dist
                                                Tools::random(btScalar(-1.0),btScalar(1.0)))); // Poid
    }

    void Synapse::connectTo(btScalar x, btScalar y, btScalar dist, btScalar weight) {
        this->connexions.append(NeuralConnexion(x, y, dist, weight));
    }

    void Synapse::disconnectTotally() {
        this->connexions.clear();
    }
}
