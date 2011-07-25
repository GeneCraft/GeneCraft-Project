#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <QObject>
#include "genelabcoreclasses.h"
#include <QDebug>
#include "tools.h"

namespace GeneLabCore {

    typedef struct NeuralConnexion {
        NeuralConnexion(btScalar x, btScalar y, btScalar distance, btScalar weight) {
            this->x = x;
            this->y = y;
            this->weight = weight;
            this->distance = distance;
        }

        /**
          * Don't take into account weight !
          */
        bool operator==(const NeuralConnexion b) {
            return this->x == b.x && this->y == b.y;
        }

        btScalar x, y;     // Connexion point. grid's pourcent position [0.0-1.0]
        btScalar weight;   // Weight of the connexion
        btScalar distance; // distance of propagation

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

        void connectRandomly() {
            this->connexions.append(NeuralConnexion(Tools::random(btScalar(0.0),btScalar(1.0)), // X
                                                    Tools::random(btScalar(0.0),btScalar(1.0)), // Y
                                                    Tools::random(btScalar(0.0),btScalar(0.2)), // dist
                                                    Tools::random(btScalar(-1.0),btScalar(1.0)))); // Poid
        }

        void connectTo(btScalar x, btScalar y, btScalar dist, btScalar weight = 1.0f) {
            this->connexions.append(NeuralConnexion(x, y, dist, weight));
        }

        void disconnectTotally() {
            this->connexions.clear();
        }

    private:
        QList<NeuralConnexion> connexions;

    };
}

#endif // SYNAPSE_H
