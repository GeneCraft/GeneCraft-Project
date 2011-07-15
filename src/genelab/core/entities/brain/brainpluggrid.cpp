#include "brainpluggrid.h"
#include "brainin.h"
#include "sinusin.h"
#include "synapse.h"
#include "brainout.h"
#include "body/treeshape.h"
#include <QDebug>
#include <cstdlib>
#include <math.h>

float sigmoid(float x)
{
     float exp_value;
     float return_value;

     /*** Exponential calculation ***/
     exp_value = exp((double) -3*x);

     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}


namespace GeneLabCore {

    BrainPlugGrid::BrainPlugGrid(const int size, QObject *parent) :
        QObject(parent)
    {
        this->size = size;
        this->neurons = new float[size*size];
        for(int i = 0; i < size*size; i++) {
            neurons[i] = 0.0f;
        }

        // On crée quelques inputs
        /*for(int i = 0; i < 3; i++) {
            NeuralIn* in = new NeuralIn(0, 100);
            for(int j = 0; j < 10; j++) {
                in->connectTo(qrand()%this->size, qrand()%this->size, (float)qrand()/RAND_MAX * 2 - 1);
            }
            this->inputs.append(in);
        }*/

        // On crée quelques outputs

        // FIXME Pour les tests :P
        this->propagation = qRound(size/10.0);
    }

    BrainPlugGrid::~BrainPlugGrid() {
        delete[] this->neurons;
    }

    float BrainPlugGrid::getValue(float x, float y) {
        return this->neurons[qRound(x * (size-1)) + qRound(y * (size-1)) * size];
    }

    void BrainPlugGrid::setSize(int size)
    {
        this->size = size;
        delete[] neurons;
        this->neurons = new float[size*size];
        for(int i = 0; i < size*size; i++)
            neurons[i] = 0.0f;

        // FIXME Pour les tests :P
        this->propagation = qRound(size/10.0);
    }

    void BrainPlugGrid::beforeStep() {

        // Clean the neurons
        for(int i = 0; i < size*size; i++) {
            this->neurons[i] = 0;
        }

        // For each inputs
        foreach(BrainIn* in, this->inputs) {
            // For each connexion of this synapse
            // If it fit in the network size
            float value = in->getValue();

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
                                    * (1 - 1 * ((float)qAbs(i - posX) / (propagation+1)))
                                    * (1 - 1 * ((float)qAbs(j - posY) / (propagation+1)));

                        }
                    }
                //}
            }
        }
    }

    void BrainPlugGrid::afterStep() {
    }

    float BrainPlugGrid::activation(float value) {
        return sigmoid(value)*2.0f - 1.0f;
    }
}
