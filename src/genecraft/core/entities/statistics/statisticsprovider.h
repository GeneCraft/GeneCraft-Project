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
