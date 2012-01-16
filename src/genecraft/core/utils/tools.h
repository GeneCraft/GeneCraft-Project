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

#ifndef TOOLS_H
#define TOOLS_H

#include "LinearMath/btScalar.h"
#include <QString>

namespace GeneCraftCore {

class Tools
{
public:
    Tools();

    static int random(int min, int max);
    //static btScalar random(btScalar min, btScalar max);

    //static btScalar normalRandom(btScalar mu=0.0, btScalar sigma=0.0);

//#ifndef BT_USE_DOUBLE_PRECISION
    static double random(double min, double max);
    static double normalRandom(double mu=0.0, double sigma=0.0);
//#endif

    // Used to remove not empty directory (recursively delete)
    static bool removeDir(QString dirPath);

    static int sign(int v) {
        return v > 0 ? 1 : (v < 0 ? -1 : 0);
    }
};

}
#endif // TOOLS_H
