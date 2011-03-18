#include "ogrebulletwindows.h"
#include "ui_ogrebulletwindows.h"

#include "graphic/ogrewidget.h"
#include "graphic/ninjascene.h".h"
#include "graphic/ogremanager.h"

#include "physics/ogrebulletmanager.h"

#include "OGRE/Ogre.h"
#include <QDebug>

OgreBulletWindows::OgreBulletWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OgreBulletWindows)
{
    ui->setupUi(this);

    ogre = new OgreManager();
    ogre->init((unsigned long)this->winId());
    Ogre::SceneManager* ogreScn    = ogre->getSceneManager();
    SceneManager* scnManager = new NinjaScene();


    scnManager->createScene(ogreScn);

    qDebug() << "camera ok";

    OgreWidget* oW1 = ogre->createOgreWidget(
                Ogre::Vector3(0,18,70), Ogre::Vector3(0, 0, -300), this->ui->centralWidget);
    this->ui->centralWidget->layout()->addWidget(oW1);
    OgreWidget* oW2 = ogre->createOgreWidget(
                Ogre::Vector3(0,18,0), Ogre::Vector3(0, 0, 70), this->ui->centralWidget);
    this->ui->centralWidget->layout()->addWidget(oW2);

    physics = new OgreBulletManager();
    physics->init(ogre);

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
    qDebug() << "update graphics..";
    ogre->oneStep();
    physics->oneStep();
}
