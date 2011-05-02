#include "neuralnetwork.h"
#include "neuralin.h"
#include "sinusin.h"
#include "synapse.h"
#include "neuralout.h"

#include <QDebug>

#include <cstdlib>

#include <math.h>

float sigmoid(float x)
{
     float exp_value;
     float return_value;

     /*** Exponential calculation ***/
     exp_value = exp((double) -x);

     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}


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
        for(int i = 0; i < 3; i++) {
            NeuralOut* out = new NeuralOut(-1, 1);
            for(int j = 0; j < 5; j++) {
                out->connectTo(qrand()%this->size, qrand()%this->size, (float)qrand()/RAND_MAX * 2 - 1);
            }
            this->outputs.append(out);
        }

        // Pour les tests :P
        for(int i = 0; i < 2; i++) {
            SinusIn* sin = new SinusIn();
            for(int j = 0; j < 5; j++) {
                sin->connectTo(qrand()%this->size, qrand()%this->size, (float)qrand()/RAND_MAX * 2 - 1);
            }
            this->inputs.append(sin);
        }
    }

    void NeuralNetwork::neuralStep() {
        qDebug() << " DO STUFF !";

        // For each ouputs
        foreach(NeuralOut* out, this->outputs) {
            float value = 0;
            foreach(NeuralConnexion connexion, out->getConnexions()) {
                // If it fit in the network size
                if(connexion.x > 0 && connexion.x < size &&
                   connexion.y > 0 && connexion.y < size) {
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
        qDebug() << " before ... !";

        // For each inputs
        foreach(NeuralIn* in, this->inputs) {
            // For each connexion of this synapse
            foreach(NeuralConnexion connexion, in->getConnexions()) {
                // If it fit in the network size
                if(connexion.x > 0 && connexion.x < size &&
                   connexion.y > 0 && connexion.y < size) {
                    // Adding this value to the cell
                    this->neurons[connexion.x + connexion.y*size]
                            += connexion.weight*in->getValue();

                }
            }
        }
    }

    void NeuralNetwork::afterStep() {
        qDebug() << " after !";

        // Clean the neurons
        for(int i = 0; i < size*size; i++) {
            this->neurons[i] = 0;
        }
    }

    float NeuralNetwork::activation(float value) {
        return sigmoid(value)*2.0f - 1.0f;
    }
}
