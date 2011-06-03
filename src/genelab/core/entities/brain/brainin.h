#ifndef NEURALIN_H
#define NEURALIN_H

#include <QObject>

#include "genelabcoreclasses.h"
#include "synapse.h"
#include <QDebug>

namespace GeneLabCore {

    class BrainIn : public Synapse
    {
        Q_OBJECT
    public:
        explicit BrainIn(float min = 0.0f, float max = 100.0f, QObject *parent = 0);
        BrainIn(QVariant data);
        QVariant serialize();

    signals:

    public slots:
        /**
          * Set the normalized value, will be normalized between min and max.
          */
        virtual void setValue(float value) {
            // Normalisation
            this->value = (value - min) / (max - min) * 2.0f - 1.0f;
            if(this->value != this->value) {
                qDebug() << "NAN IN INPUT ";
            }
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
