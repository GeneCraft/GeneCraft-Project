#ifndef NEURALIN_H
#define NEURALIN_H

#include <QObject>

#include "genecraftcoreclasses.h"
#include "synapse.h"

namespace GeneCraftCore {

    class BrainIn : public Synapse
    {

    public:
        explicit BrainIn(btScalar min = 0.0f, btScalar max = 100.0f, QObject *parent = 0);
        BrainIn(QVariant data);

        static QVariant generateEmpty(btScalar min, btScalar max);
        QVariant serialize();

        void setMin(btScalar min) { this->min = min; }
        void setMax(btScalar max) { this->max = max; }
        void setMinMax(btScalar min, btScalar max) { this->min = min; this->max = max; }

        /**
          * Set the normalized value, will be normalized between min and max.
          */
        virtual void setValue(btScalar value) {
            // Normalization (projection in range -1..1)
            this->value = (value - min) / (max - min) * 2.0f - 1.0f;
        }

        /**
          * Get the normalized value [-1, 1]
          */
        virtual btScalar getValue() {
            return this->value;
        }

    private:

        btScalar value;
        btScalar min;
        btScalar max;

    };
}

#endif // NEURALIN_H
