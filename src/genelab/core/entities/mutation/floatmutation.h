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
        float mutate(float value);
        float minFact;
        float maxFact;
        float minValue;
        float maxValue;
    };

}

#endif // FLOATMUTATION_H
