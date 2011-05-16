#ifndef NEURALNETWORKFACTORY_H
#define NEURALNETWORKFACTORY_H

#include <QObject>
#include "genelabcoreclasses.h"

namespace GeneLabCore {

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
