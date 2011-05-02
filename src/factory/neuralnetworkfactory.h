#ifndef NEURALNETWORKFACTORY_H
#define NEURALNETWORKFACTORY_H

#include <QObject>
#include "classes.h"

namespace GeneLabFactory {


    class NeuralNetworkFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit NeuralNetworkFactory(QObject *parent = 0);

    signals:

    public slots:

    };

}

#endif // NEURALNETWORKFACTORY_H
