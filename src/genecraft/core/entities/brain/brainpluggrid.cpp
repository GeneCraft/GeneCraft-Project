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

#include "brainpluggrid.h"
#include "brainin.h"
#include "sinusin.h"
#include "synapse.h"
#include "brainout.h"
#include "body/treeshape.h"
#include <QDebug>
#include <cstdlib>
#include <math.h>

btScalar sigmoid(btScalar x)
{
     btScalar exp_value;
     btScalar return_value;

     /*** Exponential calculation ***/
     exp_value = exp((double) -3*x);

     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}


namespace GeneCraftCore {

    BrainPlugGrid::BrainPlugGrid(QObject *parent) :
        QObject(parent)
    {
        //this->size = size;
        //this->neurons = new btScalar[size*size];
        //for(int i = 0; i < size*size; i++) {
        //    neurons[i] = 0.0f;
        //}

        // On cre quelques inputs
        /*for(int i = 0; i < 3; i++) {
            NeuralIn* in = new NeuralIn(0, 100);
            for(int j = 0; j < 10; j++) {
                in->connectTo(qrand()%this->size, qrand()%this->size, (btScalar)qrand()/RAND_MAX * 2 - 1);
            }
            this->inputs.append(in);
        }*/

        // On cre quelques outputs

        // FIXME Pour les tests :P
        //this->propagation = qRound(size/10.0);
    }

    BrainPlugGrid::~BrainPlugGrid() {
        //delete[] this->neurons;
    }

    btScalar BrainPlugGrid::getValue(btScalar x, btScalar y) {
        // BRAIN MODIF TRY
        btScalar value = 0;
        foreach(BrainIn* in, this->inputs) {
            foreach(NeuralConnexion c, in->getConnexions()) {
                btScalar dist = sqrt((x - c.x)*(x - c.x) + (y - c.y)*(y - c.y));
                if( dist < c.distance) {
                    value += in->getValue()*c.weight*((c.distance-dist)/c.distance);
                }
            }
        }

        return this->activation(value);
    }

    /*void BrainPlugGrid::setSize(int size)
    {
        this->size = size;
        delete[] neurons;
        this->neurons = new btScalar[size*size];
        for(int i = 0; i < size*size; i++)
            neurons[i] = 0.0f;

        // FIXME Pour les tests :P
        this->propagation = qRound(size/10.0);
    }*/

    void BrainPlugGrid::beforeStep() {

        // Clean the neurons
        // BRAIN MODIF TRY
        /*for(int i = 0; i < size*size; i++) {
            this->neurons[i] = 0;
        }*/

        // For each inputs
        // BRAIN MODIF TRY
        /*foreach(BrainIn* in, this->inputs) {
            // For each connexion of this synapse
            // If it fit in the network size
            btScalar value = in->getValue();

            foreach(NeuralConnexion connexion, in->getConnexions()) {

                int posX = qRound(connexion.x * size);
                int posY = qRound(connexion.y * size);

                //if(connexion.x >= 0 && connexion.x < size &&
                //   connexion.y >= 0 && connexion.y < size) {
                    // Adding this value to the cell

                    // FIXEM (int) n'attendra presque jamais la dernier case, utiliser round ou (int) (x + 0.5)
                    for(int i = qMax(0, posX-propagation); i <= qMin( size-1, posX+propagation); i++) {
                        for(int j = qMax(0, posY-propagation); j <= qMin(size-1, posY+propagation); j++) {
                                this->neurons[i + j*size]
                                    += connexion.weight * value
                                    * (1 - 1 * ((btScalar)qAbs(i - posX) / (propagation+1)))
                                    * (1 - 1 * ((btScalar)qAbs(j - posY) / (propagation+1)));

                        }
                    }
                //}
            }
        }*/
    }

    void BrainPlugGrid::afterStep() {
    }

    btScalar BrainPlugGrid::activation(btScalar value) {
        return sigmoid(value)*2.0f - 1.0f;
    }
}
