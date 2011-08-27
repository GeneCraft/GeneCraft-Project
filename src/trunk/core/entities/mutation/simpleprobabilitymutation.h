#ifndef SIMPLEPROBABILITYMUTATION_H
#define SIMPLEPROBABILITYMUTATION_H

#include "mutation.h"

namespace GeneCraftCore {

    class SimpleProbabilityMutation : public Mutation {
    public:

        SimpleProbabilityMutation();
        SimpleProbabilityMutation(QVariant variant);
        QVariant serialize();
    };

}

#endif // SIMPLEPROBABILITYMUTATION_H
