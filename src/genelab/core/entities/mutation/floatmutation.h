#ifndef FLOATMUTATION_H
#define FLOATMUTATION_H

#include "mutation.h"

namespace GeneLabCore {

    class FloatMutation : public Mutation {
    public:

        FloatMutation();
        FloatMutation(QVariant variant);
        QVariant serialize();

        void mutate(QVariantMap &map, QString key);
        btScalar mutate(btScalar value);
        btScalar minFact;
        btScalar maxFact;
        btScalar minValue;
        btScalar maxValue;
    };

}

#endif // FLOATMUTATION_H
