#ifndef MUTATION_H
#define MUTATION_H

#include <QVariant>

namespace GeneLabCore {

    enum MutationType { IntegerMutationType, FloatMutationType, SimpleProbabilityType };

    class Mutation {
    public:
        float probability;
        virtual void mutate(QVariantMap &map, QString key);
        bool canMutate();
        bool enable;
    };
}

#endif // MUTATION_H
