#include "structurallist.h"

#include "tools.h"
#include <QDebug>

namespace GeneLabCore {

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
