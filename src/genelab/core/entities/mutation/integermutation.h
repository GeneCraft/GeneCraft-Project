#ifndef INTEGERMUTATION_H
#define INTEGERMUTATION_H

#include "mutation.h"

namespace GeneLabCore {

    class IntegerMutation : public Mutation {
    public:
        void mutate(QVariantMap &map, QString key);
        float minFact;
        float maxFact;
        int minValue;
        int maxValue;
    };

}

#endif // INTEGERMUTATION_H
