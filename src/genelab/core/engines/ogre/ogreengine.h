#ifndef OGREMANAGER_H
#define OGREMANAGER_H

#include <QObject>
#include <QMap>

#include "genelabcoreclasses.h"
#include "engine.h"

namespace GeneLabCore {
    class OgreEngine : public GeneLabCore::Engine
    {
        Q_OBJECT
    public:
        explicit OgreEngine(unsigned long winId);


        void initOgreRoot();
        void initResources();
        void initSceneManager();

        Ogre::Root*         getOgreRoot();
        Ogre::SceneManager* getOgreSceneManager();
        OgreWidget*         createOgreWidget(QString widgetName,
                                             Ogre::Camera* cam,
                                             QWidget* parent);

        //QWidget*            getRender(QWidget* parent);

        bool isRenderable() {
            return true;
        }

        OgreWidget*         getOgreWidget(QString widgetName);

    signals:

    public slots:
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
        //QList<OgreWidget*> ogreWidgets;
        int winId;

    };
}
#endif // OGREMANAGER_H
