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

#ifndef BTFACTORY_H
#define BTFACTORY_H

#include <QObject>
#include <QMap>
#include "genecraftcoreclasses.h"

namespace GeneCraftCore {

class btFactory : public QObject
{

public:
    explicit btFactory(QObject *parent = 0);

    // To get an engine by its name
    Engine *getEngineByName(QString name);

    // To get all engines
    QMap<QString, Engine*> getEngines();

    // To get all widgets
    QMap<QString, QWidget*> getWidgets();


protected:
    QMap<QString, Engine*>         engines;
    QMap<QString, QWidget*>        widgets;
};

}

#endif // BTFACTORY_H
