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

#include "brainin.h"
#include <cstdlib>
#include <QJsonArray>

namespace GeneCraftCore {

    BrainIn::BrainIn(btScalar min, btScalar max, QObject *parent) :
        Synapse(parent), value(0), min(min), max(max)
    {
    }

    BrainIn::BrainIn(QJsonObject data) : Synapse(data["connexions"].toArray()), value(0) {
        min = data["min"].toDouble();
        max = data["max"].toDouble();
    }

    QJsonObject BrainIn::serialize() {
        QJsonObject data;

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

    QJsonObject BrainIn::generateEmpty(btScalar min, btScalar max)
    {
        QJsonObject data;

        data.insert("connexions", QJsonArray());
        data.insert("min", (double)min);
        data.insert("max", (double)max);

        return data;
    }

}
