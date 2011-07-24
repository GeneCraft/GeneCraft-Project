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

        virtual btScalar getValue() {
            deg+=inc;
            return sin((deg+offset) * SIMD_PI / 180.0f  );
        }

    private:
        btScalar deg;
        btScalar inc;
        btScalar offset;

    };
}
#endif // SINUSIN_H
