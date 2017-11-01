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

#include "boxsmellsensor.h"

#include <QVariant>

#define RADIUS_OF_SMELL 20.0

namespace GeneCraftCore {

BoxSmellSensor::BoxSmellSensor(Fixation *fixation) :
    SmellSensor(fixation, QString("Box smell sensor"), boxSmellSensor, RigidBodyOrigin::BASIC_SHAPE, RADIUS_OF_SMELL)
{
}

// To create from serialization data
BoxSmellSensor::BoxSmellSensor(QJsonObject data, Fixation * fixation) :
    SmellSensor(data, RigidBodyOrigin::BASIC_SHAPE, fixation)
{
}

QJsonObject BoxSmellSensor::generateEmpty()
{
    return SmellSensor::generateEmpty("Box smell sensor", boxSmellSensor, RADIUS_OF_SMELL);
}

}
