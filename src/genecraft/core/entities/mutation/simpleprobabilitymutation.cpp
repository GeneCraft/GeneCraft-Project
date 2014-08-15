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

#include "simpleprobabilitymutation.h"

#include <QDebug>
#include <QVariantMap>

namespace GeneCraftCore {

SimpleProbabilityMutation::SimpleProbabilityMutation(){
    probability = 1.0;
    enable      = true;
}

SimpleProbabilityMutation::SimpleProbabilityMutation(QVariant variant){
    QVariantMap map = variant.toMap();

    if(map["type"].toInt() == SimpleProbabilityType) {
        probability = map["probability"].toDouble();
        enable      = map["enable"].toBool();
    }
    else
        qDebug() << Q_FUNC_INFO << "Wrong mutation type" << map["Type"].toInt();
}

QVariant SimpleProbabilityMutation::serialize(){

    QVariantMap map;

    map.insert("type",QVariant(SimpleProbabilityType));
    map.insert("probability",QVariant((double)probability));
    map.insert("enable",QVariant(enable));

    return map;
}

}
