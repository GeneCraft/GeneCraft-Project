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

#ifndef TREESHAPESTATS_H
#define TREESHAPESTATS_H

#include "genecraftcoreclasses.h"
#include "statisticsprovider.h"
#include "statisticsstorage.h"

namespace GeneCraftCore{

class TreeShapeStats : public StatisticsProvider
{
    Q_OBJECT
public:

    TreeShapeStats(StatisticsStorage * statsStorage, TreeShape * treeshape);
    void step();

protected:

    // the treeshape
    TreeShape * treeshape;

    // Stats
    Statistic *treeshapeVerticalHeight;
    Statistic *treeshapeBones;
    Statistic *treeshapeBonesLength;
    Statistic *treeshapeWeight;
    Statistic *treeshapeNbSensors;
    Statistic *treeshapeNbEffectors;

    // to browse the shape
    void recursiveUpdate(Bone *b);

    // vertical height
    btScalar minHeightY, maxHeightY;

    // length
    btScalar length;

    // bones number
    int nbBones;

    // weight
    btScalar weight;

    // compute
    bool computeBonesNb;
    bool computeBonesLength;
    bool computeBonesWeight;
    bool computeSensorsNb;
    bool computeEffectorsNb;

protected slots:
    void reset();
};

}

#endif // TREESHAPESTATS_H
