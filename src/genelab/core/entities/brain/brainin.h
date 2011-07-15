#ifndef NEURALIN_H
#define NEURALIN_H

#include <QObject>

#include "genelabcoreclasses.h"
#include "synapse.h"
#include <QDebug>

namespace GeneLabCore {

    class BrainIn : public Synapse
    {

    public:
        explicit BrainIn(float min = 0.0f, float max = 100.0f, QObject *parent = 0);
        BrainIn(QVariant data);

        static QVariant generateEmpty(float min, float max);
        QVariant serialize();

        void setMin(float min) { this->min = min; }
        void setMax(float max) { this->max = max; }
        void setMinMax(float min, float max) { this->min = min; this->max = max; }

        /**
          * Set the normalized value, will be normalized between min and max.
          */
        virtual void setValue(float value) {
            // Normalization (projection in range -1..1)
            this->value = (value - min) / (max - min) * 2.0f - 1.0f;
        }

        /**
          * Get the normalized value [-1, 1]
          */
        virtual float getValue() {
            return this->value;
        }

    private:

        float value;
        float min;
        float max;

    };
}

#endif // NEURALIN_H
