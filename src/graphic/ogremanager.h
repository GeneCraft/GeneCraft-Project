#ifndef OGREMANAGER_H
#define OGREMANAGER_H

#include <QObject>
#include "classes.h"
#include "graphic/graphicsengine.h"

namespace GeneLabOgreBullet {
    class OgreManager : public GeneLabCore::GraphicsEngine
    {
        Q_OBJECT
    public:
        explicit OgreManager(unsigned long winId);

        void init();
        Ogre::Root* getRoot();
        Ogre::SceneManager* getOgreScene();
        GeneLabCore::GraphicsScene* getGraphicsScene();

        OgreWidget* createOgreWidget(
            Ogre::Camera* cam, QWidget* parent);

    signals:

    public slots:
        void graphicsStep();

    protected:
        Ogre::Root* ogreRoot;
        Ogre::SceneManager* scnOgre;
        GeneLabCore::GraphicsScene* scnManager;
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
