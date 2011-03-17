#ifndef OGREBULLETWINDOWS_H
#define OGREBULLETWINDOWS_H

#include <QMainWindow>
#include <QTimer>

//compilation optimisation
namespace Ogre {
    class Root;
    class SceneManager;
}

namespace Ui {
    class OgreBulletWindows;
}

class OgreWidget;

class OgreBulletWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit OgreBulletWindows(QWidget *parent = 0);
    ~OgreBulletWindows();

private:
    Ui::OgreBulletWindows *ui;
    Ogre::Root* initOgreRoot();
    void initResources();
    Ogre::SceneManager* initSceneManager(Ogre::Root* ogreRoot);
    void createScene(Ogre::SceneManager* scene);

    void initRenderingSystem(Ogre::Root* ogreRoot);

    QTimer* timerGraphic;
    Ogre::Root* ogreRoot;
    OgreWidget* oW1;
    OgreWidget* oW2;

private slots:
    void updateGraphics();

};

#endif // OGREBULLETWINDOWS_H
