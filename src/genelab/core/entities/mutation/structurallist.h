#ifndef STRUCTURALLIST_H
#define STRUCTURALLIST_H

#include <QVariant>
#include <QMap>

namespace GeneLabCore {

class MutationElement {
 public:

    MutationElement(QString name, int type, float weight) {
        this->name = name;
        this->type = type;

        if(weight < 0.0)
            weight = 0.0;

        this->weight = weight;
    }

    QString name;
    int type;
    float weight;
};

class StructuralList
{
public:
    StructuralList();

    MutationElement * pickOne();

    QList<MutationElement *> elements;
};

}

#endif // STRUCTURALLIST_H
