#include "modifier.h"
#include <QVariant>
namespace GeneLabCore {

Effector::Effector(QObject *parent) :
    QObject(parent)
{

}


Effector::Effector(QVariant data) {
    this->typeName = data.toMap()["type"].toString();
}

QVariant Effector::serialize() {
    QVariantMap data;
    data.insert("type", this->typeName);
    return data;
}

}
