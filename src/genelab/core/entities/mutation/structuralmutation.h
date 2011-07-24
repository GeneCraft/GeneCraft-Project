#ifndef STRUCTURALMUTATION_H
#define STRUCTURALMUTATION_H

#include <QVariant>
#include "LinearMath/btScalar.h"

namespace GeneLabCore {

class StructuralMutation
{
public:
    StructuralMutation();
    StructuralMutation(QVariant variant);
    QVariant serialize();

    bool checkAdd();
    bool checkDelete();
    bool checkReplace();

    btScalar addProbability;
    btScalar deleteProbability;
    btScalar replaceProbability;

    bool enable;
};

}

#endif // STRUCTURALMUTATION_H
