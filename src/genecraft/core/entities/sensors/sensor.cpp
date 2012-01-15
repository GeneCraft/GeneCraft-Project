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

#include "sensor.h"
#include <QVariant>

namespace GeneCraftCore {
    Sensor::Sensor(Fixation * fixation, QObject *parent) :
        QObject(parent)
    {
        this->fixation = fixation;
    }


    Sensor::Sensor(QVariant data, Fixation* fixation) {
        this->fixation = fixation;
        this->typeName = data.toMap()["typeName"].toString();
        this->type = (SensorType)data.toMap()["type"].toInt();
    }

    QVariant Sensor::serialize() {
        QVariantMap data;
        data.insert("typeName", this->typeName);
        data.insert("type", (int)this->type);
        return data;
    }

    QVariant Sensor::generateEmpty(QString typeName, int type) {
        QVariantMap data;
        data.insert("typeName", typeName);
        data.insert("type", type);
        return data;
    }

}
