#ifndef BRAINNODEMUTATION_H
#define BRAINNODEMUTATION_H

#include "mutation.h"

namespace GeneLabCore {

    class BrainNodeMutation : public Mutation {
    public:
        void mutate(QVariantMap &map, QString key);
        btScalar minFact;
        btScalar maxFact;
        btScalar minValue;
        btScalar maxValue;
    };

}

#endif // BRAINNODEMUTATION_H
