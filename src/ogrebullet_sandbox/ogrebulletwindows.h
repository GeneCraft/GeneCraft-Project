#ifndef OGREBULLETWINDOWS_H
#define OGREBULLETWINDOWS_H

#include <QMainWindow>
#include <QTimer>
#include "classes.h"

//compilation optimisation
namespace Ui {
    class OgreBulletWindows;
}

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
    GeneLabOgreBullet::OgreWidget* oW1;
    GeneLabOgreBullet::OgreWidget* oW2;
    GeneLabOgreBullet::OgreManager* graphics;
    GeneLabOgreBullet::BulletManager*  physics;

private slots:

};

#endif // OGREBULLETWINDOWS_H
