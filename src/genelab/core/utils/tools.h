#ifndef TOOLS_H
#define TOOLS_H

namespace GeneLabCore {

class Tools
{
public:
    Tools();

    static int random(int min, int max);
    static float random(float min, float max);
    static double random(double min, double max);
};

}
#endif // TOOLS_H
