#ifndef OGREMANAGER_H
#define OGREMANAGER_H

#include <QObject>

namespace Ogre {
    class Root;
    class SceneManager;
    class Vector3;
    class RenderWindow;
}

class OgreWidget;

class OgreManager : public QObject
{
    Q_OBJECT
public:
    explicit OgreManager(QObject *parent = 0);

    void init(unsigned long winId);
    Ogre::Root* getRoot();
    Ogre::SceneManager* getSceneManager();

    OgreWidget* createOgreWidget(Ogre::Vector3 pos, Ogre::Vector3 lookat, QWidget* parent);

    void oneStep();

signals:

public slots:

protected:
    Ogre::Root* ogreRoot;
    Ogre::SceneManager* sceneManager;
    Ogre::RenderWindow* fakeRender;

    void initOgreRoot();
    void initResources();
    void initSceneManager();
    void initRenderingSystem(unsigned long winId);

    QList<OgreWidget*> ogreWidgets;

};

#endif // OGREMANAGER_H
