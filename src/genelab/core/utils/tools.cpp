#include "tools.h"
#include <ctime>
#include <cstdlib>

namespace GeneLabCore {

    Tools::Tools() {
        srand((unsigned int)time(NULL));
    }

    int Tools::random(int min, int max) {
        return (int)((max - min) * rand()/(float) RAND_MAX + min);
    }

    float Tools::random(float min, float max) {
        return ((max - min) * ((float) rand()/RAND_MAX)) + min;
    }

    double Tools::random(double min, double max) {
        return ((max - min) * ((double) rand()/RAND_MAX)) + min;
    }
}
