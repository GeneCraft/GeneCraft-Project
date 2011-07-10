#ifndef FLOATMUTATION_H
#define FLOATMUTATION_H

#include "mutation.h"

namespace GeneLabCore {

    class FloatMutation : public Mutation {
    public:
        void mutate(QVariantMap &map, QString key);
        float minFact;
        float maxFact;
        float minValue;
        float maxValue;
    };

}

#endif // FLOATMUTATION_H
