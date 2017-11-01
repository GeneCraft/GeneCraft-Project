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

#include "effector.h"
#include <QVariant>
namespace GeneCraftCore {

Effector::Effector(QString typeName, EffectorType type) : typeName(typeName), type(type)
{
}

Effector::Effector(QJsonObject data) {
    this->typeName = data["typeName"].toString();
    this->type = (EffectorType)data["type"].toInt();
}

QVariant Effector::serialize() {
    QJsonObject data;
    data.insert("typeName", this->typeName);
    data.insert("type", (int)this->type);
    return data;
}

QVariant Effector::generateEmpty(QString typeName, int type) {
    QJsonObject data;
    data.insert("typeName", typeName);
    data.insert("type", type);
    return data;
}

}
