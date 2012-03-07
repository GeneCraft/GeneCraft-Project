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
#include <QDebug>
#include "creaturefactory.h"
#include "families/genericfamily.h"
#include "entity.h"

namespace GeneCraftCore {

    Entity* CreatureFactory::createEntity(QVariant data,
                                          btShapesFactory* shapesFactory,
                                          btVector3 position) {
        QVariantMap entityData = data.toMap();

        // inside a result ?
        if(entityData["type"].toString() == "result") {
            // Decapsulate
            qDebug() << "decapsulation from result !";
            entityData = entityData["genome"].toMap();
        }

        // Version check
        if(entityData["version"].toString() != Entity::genomeVersion) {
            //error = "Version de genome anterieur au logiciel actuel";
            //qDebug() << error;

            // Maybe conversion if possible

            // else
            return NULL;
        }

        // Generic entity
        if(entityData["type"].toString() == "generic")
            return GenericFamily::createEntity(entityData, shapesFactory, position);
        // Whatever
        else if(entityData["type"].toString() == "symetric")
            return GenericFamily::createEntity(entityData, shapesFactory, position);
        // Whatever else
        return NULL;
    }
}
