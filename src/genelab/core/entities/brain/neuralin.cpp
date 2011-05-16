#include "neuralin.h"

namespace GeneLabCore {

    NeuralIn::NeuralIn(float min, float max, QObject *parent) :
        Synapse(parent), min(min), max(max)
    {
    }

}
