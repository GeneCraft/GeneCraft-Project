#ifndef TOOLS_H
#define TOOLS_H

#include "LinearMath/btScalar.h"
#include <QString>

namespace GeneCraftCore {

class Tools
{
public:
    Tools();

    static int random(int min, int max);
    //static btScalar random(btScalar min, btScalar max);

    //static btScalar normalRandom(btScalar mu=0.0, btScalar sigma=0.0);

//#ifndef BT_USE_DOUBLE_PRECISION
    static double random(double min, double max);
    static double normalRandom(double mu=0.0, double sigma=0.0);
//#endif

    // Used to remove not empty directory (recursively delete)
    static bool removeDir(QString dirPath);

    static int sign(int v) {
        return v > 0 ? 1 : (v < 0 ? -1 : 0);
    }
};

}
#endif // TOOLS_H
