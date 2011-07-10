#ifndef MUTATION_H
#define MUTATION_H

#include <QVariant>

namespace GeneLabCore {
    class Mutation {
    public:
        float probability;
        virtual void mutate(QVariantMap &map, QString key) = 0;
    };
}

#endif // MUTATION_H
