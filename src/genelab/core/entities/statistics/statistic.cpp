#include "statistic.h"

namespace GeneLabCore{

Statistic::Statistic() : value(0.0), min(FLT_MAX), max(FLT_MIN), sum(0.0), nbSteps(0), updateEachStep(false), updateWhenValueIsRequested(false),
    name(QString("No name")), unit(QString("No unit"))
{}

}
