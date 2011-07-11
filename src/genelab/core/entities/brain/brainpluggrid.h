#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include "genelabcoreclasses.h"

namespace GeneLabCore {


    class BrainPlugGrid : public QObject
    {

    public:
        explicit BrainPlugGrid(int size, QObject *parent = 0);
        ~BrainPlugGrid();

        // Size of the edge of the grid
        int getSize() {
            return this->size;
        }

        // Set the of the plug grid
        void setSize(int size);

        // Input connected to the grid
        QList<BrainIn*> getInputs() {
            return this->inputs;
        }

        // Return the value from pourcentage x/y [0.0 - 1.0]
        float getValue(float x, float y);

        // Return the entire grid
        float* getNeurons() {
            return this->neurons;
        }


        // Adding an input
        void connectInput(BrainIn* in) {
            this->inputs.append(in);
        }

        // Remove an input
        void disconnectInput(BrainIn* in) {
            this->inputs.removeAll(in);
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
        int propagation;

    };

}

#endif // NEURALNETWORK_H
