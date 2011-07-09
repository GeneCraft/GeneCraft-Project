#ifndef FIXATIONSTATS_H
#define FIXATIONSTATS_H


#include "genelabcoreclasses.h"
#include "statisticsprovider.h"
#include "statisticsstorage.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore{

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
    Statistic *fixationVelocity;
    Statistic *fixationRelativeDistance;
    Statistic *fixationAbsoluteDistance;

    // specific data
    int nbSteps;
    float sum;
    float distance;
    btVector3 previousOrigin, refOrigin;
};

}

#endif // FIXATIONSTATS_H
