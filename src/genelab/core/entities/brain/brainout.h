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
        explicit BrainOut(btScalar min = 0.0f, btScalar max = 100.0f, QObject *parent = 0);
        BrainOut(QVariant data);
        QVariant serialize();
    signals:
        void newValue(btScalar value);

    public slots:
        /**
          * Get the value, will be "unormalized" with min and max
          */
        btScalar getValue() {
            return value;
        }

        /**
          * Set the normalized value [-1, 1]
          */
        void  setValue(btScalar value) {
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

        void setMin(btScalar min) { this->min = min; }
        void setMax(btScalar max) { this->max = max; }

    private:
        btScalar min;
        btScalar max;
        btScalar value;
        QVariant connexionInfo;

    };

}
#endif // NEURALOUT_H
