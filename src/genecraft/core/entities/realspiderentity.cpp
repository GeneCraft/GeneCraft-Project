/*
Copyright 2011, 2012 David Zéni

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

#include "realspiderentity.h"
namespace GeneCraftCore {

RealSpiderEntity::RealSpiderEntity(QString name, QString family, QString type, int generation, QObject *parent):
    Entity(name, family, type, generation, parent)
{

}

void RealSpiderEntity::setup()
{
    Entity::setup();
    for(int i=0;i<leftLegs.size();i++)
    {
        ((Leg*)leftLegs.at(i))->setup(this);
    }
    for(int i=0;i<rightLegs.size();i++)
    {
        ((Leg*)rightLegs.at(i))->setup(this);
    }
}

void RealSpiderEntity::addLeftLeg(Leg *leg)
{
    leftLegs.append(leg);
}

void RealSpiderEntity::addRightLeg(Leg *leg)
{
    rightLegs.append(leg);
}

void RealSpiderEntity::removeLeftLeg(int leg)
{
    leftLegs.removeAt(leg);
}

void RealSpiderEntity::removeRightLeg(int leg)
{
    rightLegs.removeAt(leg);
}

void RealSpiderEntity::removeAllLeftLegs()
{
    leftLegs.clear();
}

void RealSpiderEntity::removeAllRightLegs()
{
    rightLegs.clear();
}

void RealSpiderEntity::removeAllLegs()
{
    removeAllRightLegs();
    removeAllLeftLegs();
}

QVariant RealSpiderEntity::serialize()
{
    QVariantMap entityVariant = Entity::serialize().toMap();

    entityVariant.insert("params", parameters.toMap());

    return entityVariant;
}

void RealSpiderEntity::setParams(QVariant params)
{
    parameters = params;
}

QVariant RealSpiderEntity::getParams()
{
    return parameters;
}

}
