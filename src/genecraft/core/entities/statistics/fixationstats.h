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

#ifndef FIXATIONSTATS_H
#define FIXATIONSTATS_H


#include "genecraftcoreclasses.h"
#include "statisticsprovider.h"
#include "statisticsstorage.h"
#include "LinearMath/btVector3.h"

namespace GeneCraftCore{

class FixationStats : public StatisticsProvider
{
    Q_OBJECT
public:

    FixationStats(StatisticsStorage * statsStorage, Fixation * fixation, QString fixName);

    void step();

public slots:
    void resetOrigin();

protected:

    // the managed fixation
    Fixation * fixation;

    // Stats
    Statistic *fixationAbsoluteVelocity;
    Statistic *fixationRelativeVelocity;
    Statistic *fixationAbsoluteYPosition;
    Statistic *fixationAbsoluteXPosition;
    Statistic *fixationAbsoluteZPosition;

    Statistic *fixationDistance;
    Statistic *fixationXPosition;
    Statistic *fixationYPosition;
    Statistic *fixationZPosition;

    // specific data
    int nbSteps;
    btScalar distance;
    btVector3 previousOriginAbs;
    btVector3 previousOriginRel,previousOriginY,previousOriginX,previousOriginZ;
    btVector3 refOriginRel, refOriginX, refOriginY, refOriginZ;
    btVector3 refDistance, refPosX, refPosY, refPosZ;
};

}

#endif // FIXATIONSTATS_H
