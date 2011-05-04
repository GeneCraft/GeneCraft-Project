#ifndef SINUSIN_H
#define SINUSIN_H
#include "classes.h"
#include <math.h>
#include "entity/neural/neuralin.h"

namespace GeneLabCore {

    class SinusIn : public NeuralIn
    {
        Q_OBJECT
    public:
        explicit SinusIn(QObject *parent = 0);

    signals:

    public slots:

        virtual float getValue() {
            deg+=inc;
            return sin(deg * M_PI / 180.0f );
        }

    private:
        int deg;
        int inc;

    };
}
#endif // SINUSIN_H
