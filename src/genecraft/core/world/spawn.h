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

#ifndef SPAWN_H
#define SPAWN_H

#include <QObject>
#include "genecraftcoreclasses.h"

#include "LinearMath/btVector3.h"

#include <QVariant>

namespace GeneCraftCore {


    class Spawn : public QObject
    {

    public:

        Spawn(QVariant data);
        Spawn(QString type, btVector3 position);
        Spawn(QString type, btVector3 topleftCorner, btVector3 bottomRightCorner);

        btVector3 getSpawnPosition();

        QString getType() { return this->type; }
        btVector3 getMinPos() { return this->minPosition; }
        btVector3 getMaxPos() { return this->maxPosition; }

    protected:
        QString type;
        // Position
        btVector3 position;
        // Zone
        btVector3 minPosition;
        btVector3 maxPosition;


    };

}

#endif // SPAWN_H
