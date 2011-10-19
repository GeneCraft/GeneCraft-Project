#ifndef NEURALOUT_H
#define NEURALOUT_H

#include <QObject>
#include <QDebug>

#include "genecraftcoreclasses.h"
#include <QVariant>

namespace GeneCraftCore {

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
        btScalar getValue();

        /**
          * Set the normalized value [-1, 1]
          */
        void  setValue(btScalar value);

        void setConnexionInfo(QVariant info);

        QVariant getConnexionInfo();

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
