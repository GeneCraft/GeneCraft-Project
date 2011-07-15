#include "structuralmutation.h"

#include "tools.h"

namespace GeneLabCore {

StructuralMutation::StructuralMutation()
{
    addProbability = .5f;
    deleteProbability = .5f;
    replaceProbability = .5f;
}

StructuralMutation::StructuralMutation(QVariant variant)
{
    addProbability = .5f;
    deleteProbability = .5f;
    replaceProbability = .5f;
}

bool StructuralMutation::checkAdd()
{
    return Tools::random(0.f,1.f) <= addProbability;
}

bool StructuralMutation::checkDelete()
{
    return Tools::random(0.f,1.f) <= deleteProbability;
}

bool StructuralMutation::checkReplace()
{
    return Tools::random(0.f,1.f) <= replaceProbability;
}

}
