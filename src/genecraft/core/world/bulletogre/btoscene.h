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

#ifndef BTOSCENE_H
#define BTOSCENE_H

#include "genecraftcoreclasses.h"
#include "btscene.h"

// Terrain
#include "Terrain/OgreTerrain.h"
#include "Terrain/OgreTerrainGroup.h"

#include "btofactory.h"

namespace GeneCraftCore {

class btoScene : public btScene
{
public:
    explicit btoScene(btoWorld* world, QVariant sceneData, QObject *parent = 0);
    ~btoScene();

    virtual void setup();
protected:
    Ogre::Terrain *mTerrain;
    Ogre::TerrainGlobalOptions *mGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
};


}

#endif // BTOSCENE_H
