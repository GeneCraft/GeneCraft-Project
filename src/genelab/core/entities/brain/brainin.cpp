#include "brainin.h"
#include <cstdlib>

namespace GeneLabCore {

    BrainIn::BrainIn(float min, float max, QObject *parent) :
        Synapse(parent), min(min), max(max)
    {
        // little cheat
        for(int i = 0; i < 1; i++) {
            this->connectTo(qrand()%20, qrand()%20, ((float)qrand())/RAND_MAX*2 -1);
        }
    }

}
