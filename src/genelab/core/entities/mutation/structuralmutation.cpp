#include "structuralmutation.h"

#include "tools.h"

#include <QDebug>

namespace GeneLabCore {

StructuralMutation::StructuralMutation()
{
    enable              = true;
    addProbability      = .5f;
    deleteProbability   = .5f;
    replaceProbability  = .5f;
}

StructuralMutation::StructuralMutation(QVariant variant)
{
    QVariantMap map = variant.toMap();

    enable              = map["enable"].toBool();
    addProbability      = map["addProbability"].toFloat();
    deleteProbability   = map["deleteProbability"].toFloat();
    replaceProbability  = map["replaceProbability"].toFloat();
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

QVariant StructuralMutation::serialize() {
    QVariantMap map;

    map.insert("enable",enable);
    map.insert("addProbability",(double)addProbability);
    map.insert("deleteProbability",(double)deleteProbability);
    map.insert("replaceProbability",(double)replaceProbability);

    return map;
}

}
