#include "statistic.h"

namespace GeneLabCore{

Statistic::Statistic() : value(0.0), updateEachStep(false), updateWhenValueIsRequested(false),
    name(QString("No name")), unit(QString("No unit"))
{}

}
