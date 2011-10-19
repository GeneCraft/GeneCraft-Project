#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <QObject>
#include "genecraftcoreclasses.h"
#include <QDebug>
#include "tools.h"

namespace GeneCraftCore {

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

        QList<NeuralConnexion> getConnexions();

        void connectRandomly();

        void connectTo(btScalar x, btScalar y, btScalar dist, btScalar weight = 1.0f);

        void disconnectTotally();
    private:
        QList<NeuralConnexion> connexions;

    };
}

#endif // SYNAPSE_H
