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

#ifndef BTOBONE_H
#define BTOBONE_H

#include "genecraftcoreclasses.h"
#include "bullet/shapes/btbone.h"
#include "Ogre.h"


namespace GeneCraftCore {

class btoBone : public btBone
{

public:
    explicit btoBone(btoWorld *world, BulletOgreEngine *btoEngine, btScalar length, btScalar radius,
                     btScalar radiusArticulation, const btTransform &transform);
    ~btoBone();
    void setup();
    void setSize(btScalar radius, btScalar height);
    void setSelected(bool selected);
    void setEndFixationRadius(btScalar radius);

    protected:

        BulletOgreEngine *btoEngine;
        Ogre::SceneNode *parentNode;
        Ogre::Entity *entityC;
        Ogre::SceneNode *nodeC;
        Ogre::Entity *entityS;
        Ogre::Entity *debugEntity;
        Ogre::SceneNode *nodeS;
        Ogre::SceneNode *debugNode;
        Ogre::SceneNode *getDebugAxes();

    private:

        static int mNumEntitiesInstanced;
        Ogre::AxisAlignedBox originalCylinderBB;


        QString boneMaterial;
        QString fixationMaterial;

        QString boneSelectedMaterial;
        QString fixationSelectedMaterial;

        Ogre::AxisAlignedBox originalSphereBB;

};
}

#endif // BTOBONE_H
