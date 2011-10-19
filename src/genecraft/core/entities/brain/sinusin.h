#ifndef SINUSIN_H
#define SINUSIN_H

#include "genecraftcoreclasses.h"
#include <math.h>

#include "brainin.h"

namespace GeneCraftCore {

    class SinusIn : public BrainIn
    {

    public:
        explicit SinusIn(QObject *parent = 0);

        virtual btScalar getValue();

    private:
        btScalar deg;
        btScalar inc;
        btScalar offset;

    };
}
#endif // SINUSIN_H
