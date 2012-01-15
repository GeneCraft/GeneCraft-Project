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

#ifndef OGREMANAGER_H
#define OGREMANAGER_H

#include <QObject>
#include <QMap>

#include "genecraftcoreclasses.h"
#include "engine.h"

namespace GeneCraftCore {
    class OgreEngine : public GeneCraftCore::Engine
    {

    public:
        explicit OgreEngine(unsigned long winId);


        void initOgreRoot();
        void initResources();
        void initSceneManager();
        void initOverlay();

        Ogre::Root*         getOgreRoot();
        Ogre::SceneManager* getOgreSceneManager();
        OgreWidget*         createOgreWidget(QString widgetName,
                                             Ogre::Camera* cam,
                                             QWidget* parent);

        OgreWidget*         getOgreWidget(QString widgetName);

        void init();
        void beforeStep();
        void step();
        void afterStep();

    protected:
        Ogre::Root*         ogreRoot;
        Ogre::SceneManager* scnManager;
        Ogre::RenderWindow* fakeRender;

        void initRenderingSystem(unsigned long winId);


        QMap<QString, OgreWidget*> ogreWidgets;
        int winId;

    };
}
#endif // OGREMANAGER_H
