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
class OgreManager;
class OgreBulletManager;

class OgreBulletWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit OgreBulletWindows(QWidget *parent = 0);
    ~OgreBulletWindows();

private:
    Ui::OgreBulletWindows *ui;


    QTimer* timerGraphic;
    Ogre::Root* ogreRoot;
    OgreWidget* oW1;
    OgreWidget* oW2;
    OgreManager* ogre;
    OgreBulletManager* physics;

private slots:
    void updateGraphics();

};

#endif // OGREBULLETWINDOWS_H
