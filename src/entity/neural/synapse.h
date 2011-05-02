#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <QObject>
#include "classes.h"

namespace GeneLabCore {

    typedef struct NeuralConnexion {
        NeuralConnexion(int x, int y, float weight) {
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

        int   x, y;   // Connexion point
        float weight; // Weight of the connexion

    } NeuralConnexion;

    class Synapse : public QObject
    {
        Q_OBJECT
    public:
        explicit Synapse(QObject *parent = 0);

        QList<NeuralConnexion> getConnexions() {
            return this->connexions;
        }

    signals:

    public slots:
        void connectTo(int x, int y, float weight = 1.0f) {
            this->connexions.append(NeuralConnexion(x, y, weight));
        }

        void disconnect(int x, int y) {
            this->connexions.removeOne(NeuralConnexion(x, y, 1));
        }

    private:
        QList<NeuralConnexion> connexions;


    };
}

#endif // SYNAPSE_H
