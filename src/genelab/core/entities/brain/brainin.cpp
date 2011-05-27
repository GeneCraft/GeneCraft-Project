#include "brainin.h"

namespace GeneLabCore {

    BrainIn::BrainIn(float min, float max, QObject *parent) :
        Synapse(parent), min(min), max(max)
    {
    }

}
