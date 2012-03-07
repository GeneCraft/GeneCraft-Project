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

#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <QObject>
#include "genecraftcoreclasses.h"
#include <QDebug>

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
