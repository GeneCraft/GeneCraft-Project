#ifndef SINUSIN_H
#define SINUSIN_H

#include "genelabcoreclasses.h"
#include <math.h>
#include "brainin.h"

namespace GeneLabCore {

    class SinusIn : public BrainIn
    {
        Q_OBJECT
    public:
        explicit SinusIn(QObject *parent = 0);

    signals:

    public slots:

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
