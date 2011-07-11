#ifndef SINUSIN_H
#define SINUSIN_H

#include "genelabcoreclasses.h"
#include <math.h>

#include "brainin.h"

namespace GeneLabCore {

    class SinusIn : public BrainIn
    {

    public:
        explicit SinusIn(QObject *parent = 0);

        virtual float getValue() {
            deg+=inc;
            return sin((deg+offset) * M_PI / 180.0f  );
        }

    private:
        float deg;
        float inc;
        float offset;

    };
}
#endif // SINUSIN_H
