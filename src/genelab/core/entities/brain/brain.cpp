#include "brain.h"
#include "brainpluggrid.h"

namespace GeneLabCore {
    Brain::Brain(int plugGridSize, QObject *parent) :
        QObject(parent)
    {
        this->plugGrid = new BrainPlugGrid(plugGridSize);
    }
}
