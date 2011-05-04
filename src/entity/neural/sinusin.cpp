#include "sinusin.h"

namespace GeneLabCore {
    SinusIn::SinusIn(QObject *parent) :
        NeuralIn(-1, 1, parent), deg(0)
    {
        inc = 1 + qrand()%4;
    }
}
