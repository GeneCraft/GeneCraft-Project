#include "btoworld.h"

#include "mainfactory.h"
#include "bulletogre/bulletogreengine.h"
#include "Ogre.h"
#include "OgreMeshManager.h"

#include "ogre/ogreengine.h"

#include <QDebug>

namespace GeneLabCore {

    btoWorld::btoWorld(MainFactory* factory, QVariant data, QObject *parent) :
        btWorld(factory, data)
    {
        btoEngine = static_cast<BulletOgreEngine*>(factory->getEngines().find("BulletOgre").value());

    }

    void btoWorld::setup(){
         btWorld::setup();
    }

}
