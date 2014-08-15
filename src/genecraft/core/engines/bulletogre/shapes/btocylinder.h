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

#ifndef BTOCYLINDER_H
#define BTOCYLINDER_H

#include "genecraftcoreclasses.h"
#include "bullet/shapes/btcylinder.h"
#include "Ogre.h"

namespace GeneCraftCore {

class btoCylinder : public btCylinder
{
public:

    btoCylinder(btoWorld *world, BulletOgreEngine *btoEngine, btScalar radius, btScalar height, const btTransform &transform, const btScalar density);
    void setup();
    void setSize(btScalar radius, btScalar height);

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

private:
    static int mNumEntitiesInstanced;
};

}

#endif // BTOCYLINDER_H
