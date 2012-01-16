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

#include "sinusin.h"

#include <cstdlib>
#include <QDebug>

namespace GeneCraftCore {
    SinusIn::SinusIn(QObject *parent) :
        BrainIn(-1, 1, parent), deg(0)
    {
        inc = 1.0f + (btScalar)qrand()/RAND_MAX * 4;
        offset = (btScalar)qrand()/RAND_MAX*360;
    }

    btScalar SinusIn::getValue() {
        deg+=inc;
        return sin((deg+offset) * SIMD_PI / 180.0f  );
    }

}
