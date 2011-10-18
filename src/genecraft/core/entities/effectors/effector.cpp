#include "effector.h"
#include <QVariant>
namespace GeneCraftCore {

Effector::Effector(QString typeName, EffectorType type) : typeName(typeName), type(type)
{
}

Effector::Effector(QVariant data) {
    this->typeName = data.toMap()["typeName"].toString();
    this->type = (EffectorType)data.toMap()["type"].toInt();
}

QVariant Effector::serialize() {
    QVariantMap data;
    data.insert("typeName", this->typeName);
    data.insert("type", (int)this->type);
    return data;
}

QVariant Effector::generateEmpty(QString typeName, int type) {
    QVariantMap data;
    data.insert("typeName", typeName);
    data.insert("type", type);
    return data;
}

}
