#ifndef TREESHAPESTATS_H
#define TREESHAPESTATS_H

#include "genelabcoreclasses.h"
#include "statisticsprovider.h"
#include "statisticsstorage.h"

namespace GeneLabCore{

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
