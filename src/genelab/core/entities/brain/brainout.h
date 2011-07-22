#ifndef NEURALOUT_H
#define NEURALOUT_H

#include <QObject>
#include <QDebug>

#include "genelabcoreclasses.h"
#include <QVariant>

namespace GeneLabCore {

    class BrainOut : QObject
    {
        Q_OBJECT
    public:
        explicit BrainOut(float min = 0.0f, float max = 100.0f, QObject *parent = 0);
        BrainOut(QVariant data);
        QVariant serialize();
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
            if(this->value > max) {
                this->value = max;
            }
            if(this->value < min) {
                this->value = min;
            }
            emit newValue(this->value);
        }

        void setConnexionInfo(QVariant info) {
            this->connexionInfo = info;
        }

        QVariant getConnexionInfo() {
            return this->connexionInfo;
        }

        void setMin(float min) { this->min = min; }
        void setMax(float max) { this->max = max; }

    private:
        float min;
        float max;
        float value;
        QVariant connexionInfo;

    };

}
#endif // NEURALOUT_H
