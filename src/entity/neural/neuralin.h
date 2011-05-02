#ifndef NEURALIN_H
#define NEURALIN_H

#include <QObject>

#include "classes.h"
#include "entity/neural/synapse.h"

namespace GeneLabCore {

    class NeuralIn : public Synapse
    {
        Q_OBJECT
    public:
        explicit NeuralIn(float min = 0.0f, float max = 100.0f, QObject *parent = 0);

    signals:

    public slots:
        /**
          * Set the normalized value, will be normalized between min and max.
          */
        virtual void setValue(float value) {
            // Normalisation
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
