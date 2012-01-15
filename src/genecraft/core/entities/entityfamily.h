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

#ifndef ENTITYFAMILY_H
#define ENTITYFAMILY_H

#include <QObject>
#include "genecraftcoreclasses.h"
#include "LinearMath/btVector3.h"

namespace GeneCraftCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * A Family allows to create specific entities with particular shape.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class EntityFamily : public QObject
{

public:
    explicit EntityFamily(QObject *parent = 0);

    virtual Entity* createEntity(btShapesFactory *shapesFactory, const btVector3 &position) = 0;

    virtual QVariant serialize() = 0;

};
}
#endif // ENTITYFAMILY_H
