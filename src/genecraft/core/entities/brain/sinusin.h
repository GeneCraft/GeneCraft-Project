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

#ifndef SINUSIN_H
#define SINUSIN_H

#include "genecraftcoreclasses.h"
#include <math.h>

#include "brainin.h"

namespace GeneCraftCore {

    class SinusIn : public BrainIn
    {

    public:
        explicit SinusIn(QObject *parent = 0);

        virtual btScalar getValue();

    private:
        btScalar deg;
        btScalar inc;
        btScalar offset;

    };
}
#endif // SINUSIN_H
