#ifndef OGREMANAGER_H
#define OGREMANAGER_H

#include <QObject>
#include "classes.h"
#include "engine/engine.h"

namespace GeneLabOgreBullet {
    class OgreManager : public GeneLabCore::Engine
    {
        Q_OBJECT
    public:
        explicit OgreManager(unsigned long winId);

        Ogre::Root*         getOgreRoot();
        Ogre::SceneManager* getOgreSceneManager();
        OgreScene*          getOgreScene();

        OgreWidget*         createOgreWidget(Ogre::Camera* cam,
                                             QWidget* parent);

        QWidget*            getRender(QWidget* parent);

        bool isRenderable() {
            return true;
        }


    signals:

    public slots:
        void init();
        void beforeStep();
        void step();
        void afterStep();

    protected:
        Ogre::Root*         ogreRoot;
        Ogre::SceneManager* scnManager;
        OgreScene*          scnOgre;
        Ogre::RenderWindow* fakeRender;

        void initOgreRoot();
        void initResources();
        void initSceneManager();
        void initRenderingSystem(unsigned long winId);

        QList<OgreWidget*> ogreWidgets;
        int winId;

    };
}
#endif // OGREMANAGER_H
