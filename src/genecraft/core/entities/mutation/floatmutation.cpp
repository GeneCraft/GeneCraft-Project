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

#include "floatmutation.h"
#include "tools.h"

#include <QVariant>
#include <QVariantMap>
#include <QDebug>

namespace GeneCraftCore {

    FloatMutation::FloatMutation(QVariant variant)
    {
        QVariantMap map = variant.toMap();

        if(map["type"].toInt() == FloatMutationType) {
            probability = map["probability"].toDouble();
            if(map.contains("mean")) {
                mean      = map["mean"].toDouble();
                sigma     = map["sigma"].toDouble();
            } else {
                probability = 1.0;
                mean = 0.0;
                sigma = 0.02;
            }
            minValue    = map["minValue"].toDouble();
            maxValue    = map["maxValue"].toDouble();
            enable      = map["enable"].toBool();
        }
        else {
            qDebug() << map;
            qDebug() << Q_FUNC_INFO << "Wrong mutation type" << map["type"].toInt();
        }
    }

    FloatMutation::FloatMutation()
    {
        probability = 1.0;
        mean      = 0.0;
        sigma     = 0.02;
        minValue    = 0.0;
        maxValue    = 1.0;
        enable      = true;
    }

    QVariant FloatMutation::serialize(){

        QVariantMap map;

        map.insert("type",QVariant(FloatMutationType));
        map.insert("probability",QVariant((double)probability));
        map.insert("mean",QVariant((double)mean));
        map.insert("sigma",QVariant((double)sigma));
        map.insert("minValue",QVariant((double)minValue));
        map.insert("maxValue",QVariant((double)maxValue));
        map.insert("enable",QVariant(enable));

        return map;
    }

    void FloatMutation::mutate(QVariantMap &map, QString key){

        btScalar newValue = this->mutate((btScalar)map.value(key).toDouble());
        map.remove(key);
        map.insert(key,(double)newValue);

    }

    btScalar FloatMutation::mutate(btScalar value) {

        // mutation ?
        if(!canMutate()) {
            return value;
        }

        //btScalar newValue = value + Tools::random(minFact, maxFact) * value;
        float v = Tools::normalRandom(mean, sigma);
        btScalar newValue = value + (maxValue - minValue) * v;

        if(newValue < minValue)
            newValue = minValue;

        if(newValue > maxValue)
            newValue = maxValue;

        return newValue;
    }
}
