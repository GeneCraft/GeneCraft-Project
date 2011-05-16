#include "neuralout.h"

namespace GeneLabCore {

    NeuralOut::NeuralOut(float min, float max, QObject *parent) :
        Synapse(parent), min(min), max(max)
    {
    }

}
