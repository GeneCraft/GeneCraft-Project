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

#include "spawn.h"

#include "tools.h"

#include <QJsonObject>
#include <QDebug>

namespace GeneCraftCore {


    Spawn::Spawn(QJsonObject dMap) {


        this->type = dMap["type"].toString();

        if(type == "position") {

            this->position = btVector3(dMap["posX"].toDouble(),
                                       dMap["posY"].toDouble(),
                                       dMap["posZ"].toDouble());
        }
        else if(type == "minMaxArea") {

            this->minPosition = btVector3(dMap["minX"].toDouble(),
                                          dMap["minY"].toDouble(),
                                          dMap["minZ"].toDouble());

            this->maxPosition = btVector3(dMap["maxX"].toDouble(),
                                          dMap["maxY"].toDouble(),
                                          dMap["maxZ"].toDouble());
        }
        else if(type == "boxArea") {

            btVector3 size(dMap["sizeX"].toDouble(),
                          dMap["sizeY"].toDouble(),
                          dMap["sizeZ"].toDouble());

            btVector3 pos(dMap["posX"].toDouble(),
                          dMap["posY"].toDouble(),
                          dMap["posZ"].toDouble());

            this->minPosition = pos - size/2.0;
            this->maxPosition = pos + size/2.0;
        }
    }

    Spawn::Spawn(QString type, btVector3 position) {
        this->type = type;
        this->position = position;
    }

    Spawn::Spawn(QString type, btVector3 topleftCorner, btVector3 bottomRightCorner) {
        this->type = type;
        this->minPosition = topleftCorner;
        this->maxPosition = bottomRightCorner;
    }

    btVector3 Spawn::getSpawnPosition() {

        if(type == "position")
            return this->position;
        else if(type == "minMaxArea" || type == "boxArea") {
            btVector3 spawn = btVector3();
            spawn.setX(Tools::random(minPosition.x(), maxPosition.x()));
            spawn.setY(Tools::random(minPosition.y(), maxPosition.y()));
            spawn.setZ(Tools::random(minPosition.z(), maxPosition.z()));
            return spawn;
        }

        return btVector3(0, 10, 0);
    }

}
