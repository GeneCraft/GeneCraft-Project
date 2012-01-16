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

#ifndef NEURALOUT_H
#define NEURALOUT_H

#include <QObject>
#include <QDebug>

#include "genecraftcoreclasses.h"
#include <QVariant>

namespace GeneCraftCore {

    class BrainOut : QObject
    {
        Q_OBJECT
    public:
        explicit BrainOut(btScalar min = 0.0f, btScalar max = 100.0f, QObject *parent = 0);
        BrainOut(QVariant data);
        QVariant serialize();
    signals:
        void newValue(btScalar value);

    public slots:
        /**
          * Get the value, will be "unormalized" with min and max
          */
        btScalar getValue();

        /**
          * Set the normalized value [-1, 1]
          */
        void  setValue(btScalar value);

        void setConnexionInfo(QVariant info);

        QVariant getConnexionInfo();

        void setMin(btScalar min) { this->min = min; }
        void setMax(btScalar max) { this->max = max; }

    private:
        btScalar min;
        btScalar max;
        btScalar value;
        QVariant connexionInfo;

    };

}
#endif // NEURALOUT_H
