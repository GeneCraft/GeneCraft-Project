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

#ifndef NEURALIN_H
#define NEURALIN_H

#include <QObject>

#include "genecraftcoreclasses.h"
#include "synapse.h"

namespace GeneCraftCore {

    class BrainIn : public Synapse
    {

    public:
        explicit BrainIn(btScalar min = 0.0f, btScalar max = 100.0f, QObject *parent = 0);
        BrainIn(QVariant data);

        static QVariant generateEmpty(btScalar min, btScalar max);
        QVariant serialize();

        void setMin(btScalar min) { this->min = min; }
        void setMax(btScalar max) { this->max = max; }
        void setMinMax(btScalar min, btScalar max) { this->min = min; this->max = max; }

        /**
          * Set the normalized value, will be normalized between min and max.
          */
        virtual void setValue(btScalar value);

        virtual void setNonNormalizedValue(btScalar value);

        /**
          * Get the normalized value [-1, 1]
          */
        virtual btScalar getValue();

    private:

        btScalar value;
        btScalar min;
        btScalar max;

    };
}

#endif // NEURALIN_H
