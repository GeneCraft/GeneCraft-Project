#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include "classes.h"

namespace GeneLabCore {


    class NeuralNetwork : public QObject
    {
        Q_OBJECT
    public:
        explicit NeuralNetwork(int size, QObject *parent = 0);

        void animate(TreeShape* shape);

        int getSize() {
            return this->size;
        }
        QList<NeuralIn*> getInputs() {
            return this->inputs;
        }

        QList<NeuralOut*> getOutputs() {
            return this->outputs;
        }

        float* getNeurons() {
            return this->neurons;
        }

    signals:

    public slots:
        void connectInput(NeuralIn* in) {
            this->inputs.append(in);
        }

        void connectOutput(NeuralOut* out) {
            this->outputs.append(out);
        }

        void beforeStep();
        void neuralStep();
        void afterStep();


        // Activation function
        float activation(float value);

    private:
        QList<NeuralIn*> inputs;
        QList<NeuralOut*> outputs;

        int size;

        // size-squared neurons matrice
        float* neurons;

    };

}

#endif // NEURALNETWORK_H
