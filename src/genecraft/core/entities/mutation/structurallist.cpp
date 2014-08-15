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

#include "structurallist.h"

#include "tools.h"
#include <QDebug>

namespace GeneCraftCore {

MutationElement::MutationElement(QString name, int type, btScalar weight) {
    this->name = name;
    this->type = type;

    if(weight < 0.0)
        weight = 0.0;

    this->weight = weight;
}

MutationElement::MutationElement(QVariant variant) {
    QVariantMap map = variant.toMap();

    name = map["name"].toString();
    type = map["type"].toInt();

    if(map["weight"].toFloat() < 0.0)
        weight = 0.0;
    else
        weight = map["weight"].toFloat();
}

QVariant MutationElement::serialize() {

    QVariantMap map;

    map.insert("name",name);
    map.insert("type",type);
    map.insert("weight",(double)weight);

    return map;
}

StructuralList::StructuralList(){}

StructuralList::~StructuralList() {
    qDeleteAll(this->elements);
    elements.clear();
}

StructuralList::StructuralList(QVariant variant) {
    QVariantList list = variant.toList();
    foreach(QVariant variant, list)
        elements.append(new MutationElement(variant));
}

MutationElement *StructuralList::pickOne() {
    // Compute the sum of weights
    btScalar totalWeight = 0.f;
    foreach(MutationElement *element, elements)
        totalWeight += element->weight;

    // get a random value in range
    btScalar rand = Tools::random(0.f,totalWeight);

    // find the element
    btScalar sum = 0.f;
    for(int i=0;i< elements.count();++i){

        if(sum > rand) // not possible at the first iteration
            return elements.at(i-1);

        MutationElement *element = elements.at(i);
        sum += element->weight;
    }

    // normally, it will not happen...
    return elements.last();
}

QVariant StructuralList::serialize() {
    QVariantList list;

    foreach(MutationElement *element, elements)
        list.append(element->serialize());

    return list;
}

}
