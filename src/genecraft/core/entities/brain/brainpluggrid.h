/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include "genecraftcoreclasses.h"

namespace GeneCraftCore {


    class BrainPlugGrid : public QObject
    {

    public:
        explicit BrainPlugGrid(QObject *parent = 0);
        ~BrainPlugGrid();

        // Size of the edge of the grid
        //int getSize() {
        //    return this->size;
        //}

        // Set the of the plug grid
        //void setSize(int size);

        // Input connected to the grid
        QList<BrainIn*> getInputs() {
            return this->inputs;
        }

        // Return the value from pourcentage x/y [0.0 - 1.0]
        btScalar getValue(btScalar x, btScalar y);

        // Return the entire grid
        //btScalar* getNeurons() {
        //    return this->neurons;
        //}


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
        btScalar activation(btScalar value);

    private:
        QList<BrainIn*> inputs;

        //int size;

        // size-squared neurons matrice
        //btScalar* neurons;
        int propagation;

    };

}

#endif // NEURALNETWORK_H
