#ifndef BONELIMITSMUTATION_H
#define BONELIMITSMUTATION_H

#include "mutation.h"
#include "floatmutation.h"

namespace GeneLabCore {

class BoneLimitsMutation : public Mutation
{
public:

    BoneLimitsMutation();

    // Not used !
    void mutate(QVariantMap &map, QString key){}

    // To mutate, a lower limit can't be upper than an upper limit !
    void mutate(QVariantMap &lowerLimits, QVariantMap &upperLimits);

    FloatMutation *axisMutation;

};

}

#endif // BONELIMITSMUTATION_H
