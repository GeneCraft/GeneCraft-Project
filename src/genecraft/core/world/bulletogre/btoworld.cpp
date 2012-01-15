#include "btoworld.h"

#include "btofactory.h"
#include "btoshapesfactory.h"
#include "bulletogre/bulletogreengine.h"
#include "Ogre.h"
#include "OgreMeshManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"

#include "ogre/ogreengine.h"

#include <QDebug>
#include <QVariant>
#include <QVariantMap>

namespace GeneCraftCore {


    btoWorld::btoWorld(btoFactory* factory, btoShapesFactory* shapesFactory, QObject *parent) :
        btWorld(factory, shapesFactory, parent)
    {
        btoEngine = static_cast<BulletOgreEngine*>(factory->getEngineByName("BulletOgre"));
    }

    btoWorld::btoWorld(btoFactory* factory, btoShapesFactory* shapesFactory, QVariant data, QObject *parent) :
        btWorld(factory, shapesFactory, data, parent)
    {
        btoEngine = static_cast<BulletOgreEngine*>(factory->getEngineByName("BulletOgre"));
    }

    void btoWorld::setup(){
         btWorld::setup();
    }

}
