#include "mutation.h"
#include "tools.h"

#include <QDebug>

namespace GeneCraftCore {

    void Mutation::mutate(QVariantMap &, QString){}

    bool Mutation::canMutate()
    {
        return enable && Tools::random(0.f,1.f) <= probability;
    }
}
