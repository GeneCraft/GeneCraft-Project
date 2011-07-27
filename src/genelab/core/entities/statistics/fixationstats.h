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

    // specific data
    int nbSteps;
    btScalar distance;
    btVector3 previousOriginAbs;
    btVector3 previousOriginRel,previousOriginY,previousOriginX,previousOriginZ;
    btVector3 refOriginRel, refOriginX, refOriginY, refOriginZ;
};

}

#endif // FIXATIONSTATS_H
