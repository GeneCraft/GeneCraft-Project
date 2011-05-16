#ifndef NEURALOUT_H
#define NEURALOUT_H

#include <QObject>
#include <QDebug>

#include "genelabcoreclasses.h"
#include "synapse.h"

namespace GeneLabCore {

    class NeuralOut : public Synapse
    {
        Q_OBJECT
    public:
        explicit NeuralOut(float min = 0.0f, float max = 0.0f, QObject *parent = 0);

    signals:
        void newValue(float value);

    public slots:
        /**
          * Get the value, will be "unormalized" with min and max
          */
        float getValue() {
            return value;
        }

        /**
          * Set the normalized value [-1, 1]
          */
        void  setValue(float value) {
            // Un noramlization
            this->value = (value + 1.0f) / 2.0f * (max - min) + min;
            if(this->value > 1) {
                this->value = 1;
            }
            if(this->value < -1) {
                this->value = -1;
            }
            emit newValue(this->value);
        }

    private:
        float min;
        float max;
        float value;

    };

}
#endif // NEURALOUT_H
