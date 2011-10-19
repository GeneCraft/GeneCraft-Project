#ifndef STATISTICSPROVIDER_H
#define STATISTICSPROVIDER_H

#include <QString>
#include <QDebug>
#include "genecraftcoreclasses.h"

namespace GeneCraftCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Main class of all statistics providers. Statistics providers is used to put information into the statistic
 * Theses information are about entities abilities or characteristics.
 * Statistics notions is used to apply natural selection.
 *
 * @version 1.0 | July 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class StatisticsProvider : public QObject
{

public:
    StatisticsProvider(StatisticsStorage * statsStorage);

    // To step the statistic
    virtual void step() = 0;

protected:

    // The Statistics Storage
    StatisticsStorage *statsStorage;
};

}

#endif // STATISTICSPROVIDER_H
