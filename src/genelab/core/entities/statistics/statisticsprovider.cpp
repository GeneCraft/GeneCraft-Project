#include "statisticsprovider.h"

#include "statistics/statisticsstorage.h"

namespace GeneCraftCore {

StatisticsProvider::StatisticsProvider(StatisticsStorage *statsStorage) : statsStorage(statsStorage) //, value(0.0), min(FLT_MAX), max(FLT_MIN), sum(0.0), nbSteps(0), updateEachStep(false), updateWhenValueIsRequested(false),
{
}

}
