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

#include "structuralmutation.h"

#include "tools.h"

#include <QDebug>

namespace GeneCraftCore {

StructuralMutation::StructuralMutation()
{
    enable              = true;
    addProbability      = .5f;
    deleteProbability   = .5f;
    replaceProbability  = .5f;
}

StructuralMutation::StructuralMutation(QJsonObject map)
{

    enable              = map["enable"].toBool();
    addProbability      = map["addProbability"].toDouble();
    deleteProbability   = map["deleteProbability"].toDouble();
    replaceProbability  = map["replaceProbability"].toDouble();
}

bool StructuralMutation::checkAdd()
{
    return enable && Tools::random(0.f,1.f) <= addProbability;
}

bool StructuralMutation::checkDelete()
{
    return enable && Tools::random(0.f,1.f) <= deleteProbability;
}

bool StructuralMutation::checkReplace()
{
    return enable && Tools::random(0.f,1.f) <= replaceProbability;
}

QJsonObject StructuralMutation::serialize() {
    QJsonObject map;

    map.insert("enable",enable);
    map.insert("addProbability",(double)addProbability);
    map.insert("deleteProbability",(double)deleteProbability);
    map.insert("replaceProbability",(double)replaceProbability);

    return map;
}

}
