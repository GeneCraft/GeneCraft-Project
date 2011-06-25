#ifndef OGREBULLETWINDOWS_H
#define OGREBULLETWINDOWS_H

#include <QMainWindow>
#include <QTimer>
#include "genelabcoreclasses.h"

//compilation optimisation
namespace Ui {
    class OgreBulletWindows;
}

namespace GeneLabCore {
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
    OgreEngine* ogreEngine;
    BulletEngine*  bulletEngine;
    btoFactory* factory;

private slots:

};
}
#endif // OGREBULLETWINDOWS_H
