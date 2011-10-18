#ifndef INTEGERMUTATION_H
#define INTEGERMUTATION_H

#include "mutation.h"

namespace GeneCraftCore {

    class IntegerMutation : public Mutation {
    public:

        IntegerMutation(QVariant variant);
        IntegerMutation();
        QVariant serialize();

        void mutate(QVariantMap &map, QString key);
        int mutate(int value);
        int minIncr;
        int maxIncr;
        int minValue;
        int maxValue;
    };

}

#endif // INTEGERMUTATION_H
