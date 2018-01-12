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

#ifndef BTOSPHERE_H
#define BTOSPHERE_H

#include "genecraftcoreclasses.h"
#include "bullet/shapes/btsphere.h"
#include "Ogre.h"
#include <QJsonObject>

namespace GeneCraftCore {

class btoSphere : public btSphere
{
public:
    btoSphere(btoWorld *world, BulletOgreEngine *btoEngine, btScalar radius, const btTransform &transform, const btScalar density, QJsonObject params = QJsonObject());
    ~btoSphere();
    void setup();
    void setSelected(bool selected);
    void setRadius(btScalar radius);

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

    QString fixationMaterial;
    QString fixationSelectedMaterial;
    Ogre::AxisAlignedBox originalSphereBB;

private:
    static int mNumSpheresInstanced;
};

}

#endif // BTOSPHERE_H
