#include "sinusin.h"

#include <cstdlib>
#include <QDebug>

namespace GeneLabCore {
    SinusIn::SinusIn(QObject *parent) :
        BrainIn(-1, 1, parent), deg(0)
    {
        inc = 1.0f + (float)qrand()/RAND_MAX * 4;
        offset = (float)qrand()/RAND_MAX*360;
    }
}
