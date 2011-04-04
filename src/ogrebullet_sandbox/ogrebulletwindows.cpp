#include "ogrebulletwindows.h"
#include "ui_ogrebulletwindows.h"

#include "graphic/ogremanager.h"
#include "graphic/ogrewidget.h"
#include "graphic/ogrescene.h"

#include "physics/bulletmanager.h"
#include "world/ogrebulletworld.h"

#include "factory/jsonloader.h"

#include "OGRE/Ogre.h"
#include <QDebug>

#include "defaulteventmanager.h"

OgreBulletWindows::OgreBulletWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OgreBulletWindows)
{
    ui->setupUi(this);

    // --
    // -- Graphics : Ogre
    // --
    qDebug() << "Init Ogre";
    graphics = new GeneLabOgreBullet::OgreManager((unsigned long)this->winId());
    graphics->init();
    qDebug() << "[OK]\n";

    //qDebug() << "Create Scene";
    //GeneLabOgreBullet::OgreScene* scn = new GeneLabOgreBullet::OgreScene();

    qDebug() << "Init Cameras";
    // camera 1
    Ogre::Camera* cam1 = graphics->getOgreSceneManager()->createCamera("first");
    cam1->setPosition(Ogre::Vector3(0, 18, 70));
    cam1->lookAt(Ogre::Vector3(0, 0, -300));
    cam1->setNearClipDistance(5);

    // camera 2
    Ogre::Camera* cam2 = graphics->getOgreSceneManager()->createCamera("second");
    cam2->setPosition(Ogre::Vector3(0, 18, 0));
    cam2->lookAt(Ogre::Vector3(0, 0, 70));
    cam2->setNearClipDistance(5);
    qDebug() << "[OK]\n";

    qDebug() << "Init Widgets";
    // widget 1
    QWidget*    oW1 = graphics->createOgreWidget(cam1, this->ui->centralWidget);
    QWidget*    oW2 = graphics->createOgreWidget(cam2, this->ui->centralWidget);

    // widget 2
    this->ui->centralWidget->layout()->addWidget(oW1);
    this->ui->centralWidget->layout()->addWidget(oW2);

    // --
    // -- Physics : Bullet
    // --
    qDebug() << "Init Physics";
    physics = new GeneLabOgreBullet::BulletManager();
    physics->init(this->graphics);
    qDebug() << "[OK]\n";


    // --
    // -- Events
    // --
    qDebug() << "Init Events Manager";
    // Events
    DefaultEventManager *em = new DefaultEventManager(graphics,physics->getWorld());
    connect(oW1,SIGNAL(mousePressed(QMouseEvent*)),em,SLOT(mousePressEvent(QMouseEvent*)));
    connect(oW1,SIGNAL(mouseReleased(QMouseEvent*)),em,SLOT(mouseReleaseEvent(QMouseEvent*)));
    connect(oW1,SIGNAL(mouseMoved(QMouseEvent*)),em,SLOT(mouseMoveEvent(QMouseEvent*)));

    connect(oW1,SIGNAL(keyPressed(QKeyEvent*)),em,SLOT(keyPressEvent(QKeyEvent*)));
    connect(oW1,SIGNAL(keyReleased(QKeyEvent*)),em,SLOT(keyReleaseEvent(QKeyEvent*)));

    connect(oW1,SIGNAL(entered(QEvent*)),em,SLOT(enterViewPortEvent(QEvent*)));
    connect(oW1,SIGNAL(leaved(QEvent*)),em,SLOT(leaveViewPortEvent(QEvent*)));

    qDebug() << "[OK]\n";



    // --
    // -- World
    // --
    qDebug() << "Init World";
    GeneLabCore::World* world = new GeneLabOgreBullet::OgreBulletWorld(physics,graphics,em);
    world->setup();
    qDebug() << "[OK]\n";

    qDebug() << "Start World";
    world->start();
    qDebug() << "[OK]\n";
}

OgreBulletWindows::~OgreBulletWindows()
{
    delete ui;
}

void OgreBulletWindows::updateGraphics() {
//    qDebug() << "update graphics..";
//    graphics->beforeStep();
//    physics->beforeStep();
//    graphics->step();
//    physics ->step();
//    graphics->afterStep();
//    physics->afterStep();
}
