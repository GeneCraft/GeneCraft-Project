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

#ifndef BTOFACTORY_H
#define BTOFACTORY_H

#include "genecraftcoreclasses.h"
#include "btfactory.h"

namespace GeneCraftCore {

class btoFactory : public btFactory
{
    Q_OBJECT
public:
    explicit btoFactory(QWidget* sceneWidget, unsigned long winId, QObject *parent = 0);

signals:

public slots:

};
}

#endif // BTOFACTORY_H
