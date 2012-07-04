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

#include "creaturefactory.h"
#include "families/genericfamily.h"
#include "families/realspiderfamily.h"
#include "families/antfamily.h"
#include "families/caterpillarfamily.h"
#include "families/snakefamily.h"
#include "families/spiderfamily.h"
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
    QVariant haha = entityData["origins"];
    qDebug() << "TYPE : " << entityData["type"].toString();
    qDebug() << entityData.keys();
    qDebug() << haha.toMap().values();

    // Generic entity
    if(entityData["type"].toString() == "generic")
        return GenericFamily::createEntity(entityData, shapesFactory, position);
    // Whatever
    else if(entityData["type"].toString() == "symetric")
        return GenericFamily::createEntity(entityData, shapesFactory, position);
    else if(entityData["type"].toString() == "realSpider")
    {
        RealSpiderFamily* r = new RealSpiderFamily();
        Entity* e = r->createEntity(entityData, shapesFactory, position);
        delete r;
        return e;
    }
    // Whatever else
    return NULL;
}

QVariant CreatureFactory::serialize(Entity* ent)
{
    EntityFamily* family;
    if(ent->getType() == "realSpider")
    {
        family = new RealSpiderFamily();
    }
    else if(ent->getType() == "spider") {
        family = new SpiderFamily();
    }
    else if(ent->getType() == "ant") {
        family = new AntFamily();
    }
    else if(ent->getType() == "snake") {
        family = new SnakeFamily();
    }
    else if(ent->getType() == "caterpillar") {
        family = new CaterpillarFamily();
    }
    else{
    }
    return family->serialize(ent);
}
}
