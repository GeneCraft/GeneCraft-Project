#include "neuralnetwork.h"
#include "neuralin.h"
#include "sinusin.h"
#include "synapse.h"
#include "neuralout.h"
#include "treeshape.h"
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


#define PROPAGATION 5
#define PROPAGATION_DIMINUTION 1.f

namespace GeneLabCore {

    NeuralNetwork::NeuralNetwork(const int size, QObject *parent) :
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
        for(int i = 0; i < 10; i++) {
            NeuralOut* out = new NeuralOut(-1, 1);
            for(int j = 0; j < 3; j++) {
                out->connectTo(qrand()%this->size, qrand()%this->size, (float)qrand()/RAND_MAX * 1.5 - 0.5);
            }
            this->outputs.append(out);
        }

        // Pour les tests :P
        for(int i = 0; i < 200; i++) {
            SinusIn* sin = new SinusIn();
            for(int j = 0; j < 1; j++) {
                int x = qrand()%this->size;
                int y = qrand()%this->size;
                sin->connectTo(x, y, 1);
                sin->connectTo(size - x, y, 1);
            }
            this->inputs.append(sin);
        }
    }

    void NeuralNetwork::neuralStep() {
        // For each ouputs
        foreach(NeuralOut* out, this->outputs) {
            float value = 0;
            foreach(NeuralConnexion connexion, out->getConnexions()) {
                // If it fit in the network size
                if(connexion.x >= 0 && connexion.x < size &&
                   connexion.y >= 0 && connexion.y < size) {
                    // Adding this value to the cell
                    // Do the activation function

                    value += activation(
                        this->neurons[connexion.x + connexion.y*size]
                                      ) * connexion.weight;

                }
            }

            out->setValue(value);
        }

    }

    void NeuralNetwork::beforeStep() {


        // Clean the neurons
        for(int i = 0; i < size*size; i++) {
            this->neurons[i] = 0;
        }

        // For each inputs
        foreach(NeuralIn* in, this->inputs) {
            // For each connexion of this synapse
            foreach(NeuralConnexion connexion, in->getConnexions()) {
                // If it fit in the network size
                float value = in->getValue();
                if(connexion.x >= 0 && connexion.x < size &&
                   connexion.y >= 0 && connexion.y < size) {
                    // Adding this value to the cell
                    for(int i = qMax(0, connexion.x-PROPAGATION); i <= qMin( size-1, connexion.x + PROPAGATION); i++) {
                        for(int j = qMax(0, connexion.y -PROPAGATION); j <= qMin(size-1, PROPAGATION + connexion.y); j++) {
                             this->neurons[i + j*size]
                                    += connexion.weight * value
                                    * (1 - PROPAGATION_DIMINUTION * ((float)qAbs(i - connexion.x) / (PROPAGATION+1)))
                                    * (1 - PROPAGATION_DIMINUTION * ((float)qAbs(j - connexion.y) / (PROPAGATION+1))) ;

                        }
                    }
                }
            }
        }
    }

    void NeuralNetwork::afterStep() {
    }

    float NeuralNetwork::activation(float value) {
        return sigmoid(value)*2.0f - 1.0f;
    }

    void NeuralNetwork::animate(TreeShape *shape) {

    }
}
