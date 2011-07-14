#include "mutation.h"
#include "tools.h"

namespace GeneLabCore {

    void Mutation::mutate(QVariantMap &, QString){}

    bool Mutation::canMutate()
    {
        return enable && Tools::random(0.f,1.f) > probability;
    }
}
