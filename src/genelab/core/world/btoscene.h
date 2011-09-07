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
