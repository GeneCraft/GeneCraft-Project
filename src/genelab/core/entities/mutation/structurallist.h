#ifndef STRUCTURALLIST_H
#define STRUCTURALLIST_H

#include <QVariant>
#include <QMap>

namespace GeneLabCore {

class MutationElement {
 public:

    MutationElement(QString name, int type, float weight);
    MutationElement(QVariant variant);
    QVariant serialize();

    QString name;
    int type;
    float weight;
};

class StructuralList
{
public:
    StructuralList();
    StructuralList(QVariant variant);
    QVariant serialize();

    MutationElement * pickOne();
    QList<MutationElement *> elements;
};

}

#endif // STRUCTURALLIST_H
