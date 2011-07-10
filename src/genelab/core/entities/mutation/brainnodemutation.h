#ifndef BRAINNODEMUTATION_H
#define BRAINNODEMUTATION_H

#include "mutation.h"

namespace GeneLabCore {

    class BrainNodeMutation : public Mutation {
    public:
        void mutate(QVariantMap &map, QString key);
        float minFact;
        float maxFact;
        float minValue;
        float maxValue;
    };

}

#endif // BRAINNODEMUTATION_H
