#include "brainin.h"

namespace GeneLabCore {

    BrainIn::BrainIn(float min, float max, QObject *parent) :
        Synapse(parent), min(min), max(max)
    {
        // little cheat
        for(int i = 0; i < 2; i++) {
            this->connectTo(qrand()%10, qrand()%10, 1);
        }
    }

}
