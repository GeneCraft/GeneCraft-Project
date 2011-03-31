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

OgreBulletWindows::OgreBulletWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OgreBulletWindows)
{
    ui->setupUi(this);

    graphics = new GeneLabOgreBullet::OgreManager((unsigned long)this->winId());
    graphics->init();

    GeneLabOgreBullet::OgreScene* scn = graphics->getGraphicsScene();
    GeneLabCore::World* world = new GeneLabOgreBullet::OgreBulletWorld();

    qDebug() << "camera ok";
    Ogre::Camera* cam1 = graphics->getOgreScene()->createCamera("first");
    cam1->setPosition(Ogre::Vector3(0, 18, 70));
    cam1->lookAt(Ogre::Vector3(0, 0, -300));
    cam1->setNearClipDistance(5);

    Ogre::Camera* cam2 = graphics->getOgreScene()->createCamera("second");
    cam2->setPosition(Ogre::Vector3(0, 18, 0));
    cam2->lookAt(Ogre::Vector3(0, 0, 70));
    cam2->setNearClipDistance(5);

    QWidget*    oW1 = graphics->createOgreWidget(
                cam1, this->ui->centralWidget);
    this->ui->centralWidget->layout()->addWidget(oW1);

    /*QWidget*    oW2 = graphics->createOgreWidget(
                Ogre::Vector3(0,18,0), Ogre::Vector3(0, 0, 70), this->ui->centralWidget);
    GeneLabOgreBullet::OgreWidget* oW2 = graphics->createOgreWidget(
                cam2, this->ui->centralWidget);
    this->ui->centralWidget->layout()->addWidget(oW2);*/

    physics = new GeneLabOgreBullet::BulletManager();
    physics->init(this->graphics);

    //OgreWidget* oW2 = ogre->createOgreWidget();


/*    oW2 = new OgreWidget(ogreRoot, sceneMgr, camera2, this->ui->centralWidget);
    this->ui->centralWidget->layout()->addWidget(oW2);
    oW2->init();
*/
    qDebug() << "ow ok";


    timerGraphic = new QTimer();
    timerGraphic->setInterval(1000/30); // 30fps
    timerGraphic->start();
    connect(timerGraphic, SIGNAL(timeout()), this, SLOT(updateGraphics()));

}

OgreBulletWindows::~OgreBulletWindows()
{
    delete ui;
}

void OgreBulletWindows::updateGraphics() {
    //qDebug() << "update graphics..";
    graphics->beforeStep();
    physics->beforeStep();
    graphics->step();
    physics ->step();
    graphics->afterStep();
    physics->afterStep();
}
