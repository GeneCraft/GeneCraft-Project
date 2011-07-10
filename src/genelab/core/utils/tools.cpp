#include "tools.h"
#include <ctime>
#include <cstdlib>
#include <QDebug>

namespace GeneLabCore {

    Tools::Tools() {
        qsrand((unsigned int)time(NULL));
    }

    int Tools::random(int min, int max) {
        //return (int)((max - min) * qrand()/(float) RAND_MAX + min);
        //return min+int((max-min)*(float)qrand()/(RAND_MAX));
        return min + (qrand() % (int)(max - min + 1));
    }

    float Tools::random(float min, float max) {
        return ((max - min) * ((float) qrand()/RAND_MAX)) + min;
    }

    double Tools::random(double min, double max) {
        return ((max - min) * ((double) qrand()/RAND_MAX)) + min;
    }
}
