#ifndef SIMPLEPROBABILITYMUTATION_H
#define SIMPLEPROBABILITYMUTATION_H

#include "mutation.h"

namespace GeneLabCore {

    class SimpleProbabilityMutation : public Mutation {
    public:

        SimpleProbabilityMutation();
        SimpleProbabilityMutation(QVariant variant);
        QVariant serialize();
    };

}

#endif // SIMPLEPROBABILITYMUTATION_H
