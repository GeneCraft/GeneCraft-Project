#ifndef STRUCTURALMUTATION_H
#define STRUCTURALMUTATION_H

#include <QVariant>

namespace GeneLabCore {

class StructuralMutation
{
public:
    StructuralMutation();
    StructuralMutation(QVariant variant);

    bool checkAdd();
    bool checkDelete();
    bool checkReplace();

    float addProbability;
    float deleteProbability;
    float replaceProbability;
};

}

#endif // STRUCTURALMUTATION_H
