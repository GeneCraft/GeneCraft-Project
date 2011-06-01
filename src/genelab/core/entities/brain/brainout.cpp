#include "brainout.h"

namespace GeneLabCore {

    BrainOut::BrainOut(float min, float max, QObject *parent) :
        min(min), max(max), value((min + max) / 2.0)
    {
    }
}
