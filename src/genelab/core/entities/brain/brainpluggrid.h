#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include "genelabcoreclasses.h"

namespace GeneLabCore {


    class BrainPlugGrid : public QObject
    {
        Q_OBJECT
    public:
        explicit BrainPlugGrid(int size, QObject *parent = 0);

        // Size of the edge of the grid
        int getSize() {
            return this->size;
        }

        // Input connected to the grid
        QList<BrainIn*> getInputs() {
            return this->inputs;
        }

        // Return the value from the grid in x/y
        float getValue(int x, int y);

        // Return the entire grid
        float* getNeurons() {
            return this->neurons;
        }

    signals:

    public slots:
        // Adding an input
        void connectInput(BrainIn* in) {
            this->inputs.append(in);
        }

        // Get value must be called in between those two call

        // Fill the grid
        void beforeStep();

        // Empty the grid
        void afterStep();

        // Activation function
        float activation(float value);

    private:
        QList<BrainIn*> inputs;

        int size;

        // size-squared neurons matrice
        float* neurons;

    };

}

#endif // NEURALNETWORK_H
