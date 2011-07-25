#ifndef STRUCTURALLIST_H
#define STRUCTURALLIST_H

#include <QVariant>
#include <QMap>
#include "LinearMath/btScalar.h"

namespace GeneLabCore {

class MutationElement {
 public:

    MutationElement(QString name, int type, btScalar weight);
    MutationElement(QVariant variant);
    QVariant serialize();

    QString name;
    int type;
    btScalar weight;
};

class StructuralList
{
public:
    StructuralList();
    StructuralList(QVariant variant);
    ~StructuralList();
    QVariant serialize();

    MutationElement * pickOne();
    QList<MutationElement *> elements;
};

}

#endif // STRUCTURALLIST_H
