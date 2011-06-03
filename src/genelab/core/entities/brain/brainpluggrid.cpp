#include "brainpluggrid.h"
#include "brainin.h"
#include "sinusin.h"
#include "synapse.h"
#include "brainout.h"
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


#define PROPAGATION 3
#define PROPAGATION_DIMINUTION 1.f

namespace GeneLabCore {

    BrainPlugGrid::BrainPlugGrid(const int size, QObject *parent) :
        QObject(parent)
    {
        this->size = size;
        this->neurons = new float[size*size];
        for(int i = 0; i < size*size; i++) {
            neurons[i] = 0.0f;
        }

        // On cr�e quelques inputs
        /*for(int i = 0; i < 3; i++) {
            NeuralIn* in = new NeuralIn(0, 100);
            for(int j = 0; j < 10; j++) {
                in->connectTo(qrand()%this->size, qrand()%this->size, (float)qrand()/RAND_MAX * 2 - 1);
            }
            this->inputs.append(in);
        }*/


        // On cr�e quelques outputs


        // Pour les tests :P
        for(int i = 0; i < 1; i++) {
            SinusIn* sin = new SinusIn();
            for(int j = 0; j < 0; j++) {
                int x = qrand()%this->size;
                int y = qrand()%this->size;
                sin->connectTo(x, y, 1);
                sin->connectTo(size - x, y, 1);
            }
            this->inputs.append(sin);
        }
    }

    float BrainPlugGrid::getValue(int x, int y) {
        float v = this->neurons[x + y * size];
        return v;
    }

    void BrainPlugGrid::beforeStep() {


        // Clean the neurons
        for(int i = 0; i < size*size; i++) {
            this->neurons[i] = 0;
        }

        // For each inputs
        foreach(BrainIn* in, this->inputs) {
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

    void BrainPlugGrid::afterStep() {
    }

    float BrainPlugGrid::activation(float value) {
        return sigmoid(value)*2.0f - 1.0f;
    }
}
