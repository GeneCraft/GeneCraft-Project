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
