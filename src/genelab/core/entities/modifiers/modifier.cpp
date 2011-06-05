#include "modifier.h"
#include <QVariant>
namespace GeneLabCore {

Modifier::Modifier(QObject *parent) :
    QObject(parent)
{

}


Modifier::Modifier(QVariant data) {
    this->typeName = data.toMap()["type"].toString();
}

QVariant Modifier::serialize() {
    QVariantMap data;
    data.insert("type", this->typeName);
    return data;
}

}
