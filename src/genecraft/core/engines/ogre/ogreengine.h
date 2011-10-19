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
