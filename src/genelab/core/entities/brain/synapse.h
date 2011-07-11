#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <QObject>
#include "genelabcoreclasses.h"
#include <QDebug>

namespace GeneLabCore {

    typedef struct NeuralConnexion {
        NeuralConnexion(float x, float y, float weight) {
            this->x = x;
            this->y = y;
            this->weight = weight;
        }

        /**
          * Don't take into account weight !
          */
        bool operator==(const NeuralConnexion b) {
            return this->x == b.x && this->y == b.y;
        }

        float x, y;   // Connexion point. grid's pourcent position [0.0-1.0]
        float weight; // Weight of the connexion

    } NeuralConnexion;

    class Synapse : public QObject
    {

    public:
        explicit Synapse(QObject *parent = 0);
        Synapse(QVariant data);
        QVariant serialize();

        QList<NeuralConnexion> getConnexions() {
            return this->connexions;
        }

        void connectTo(float x, float y, float weight = 1.0f) {
            this->connexions.append(NeuralConnexion(x, y, weight));
        }

        void disconnectTotally() {
            this->connexions.clear();
        }

    private:
        QList<NeuralConnexion> connexions;

    };
}

#endif // SYNAPSE_H
