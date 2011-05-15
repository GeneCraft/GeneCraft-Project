#include "mainfactory.h"
#include <QDebug>

#include "OGRE/Ogre.h"

#include "graphic/ogremanager.h"
#include "graphic/ogrewidget.h"
#include "graphic/ogreinputmanager.h"
#include "graphic/ogrescene.h"

#include "physics/bulletmanager.h"
#include "physics/bulletscene.h"

#include "graphic/eventmanager.h"

#include "input/creatureviewerinputmanager.h"

#include "factory/ressource.h"

#include "engine/brainengine.h"

#include <QLayout>

namespace GeneLabFactory {

    MainFactory::MainFactory(QWidget* sceneWidget, unsigned long winId, QObject *parent) :
        QObject(parent)
    {

        // ---------------------
        // -- Graphics : Ogre --
        // ---------------------

        // Création des différents engines
        qDebug() << "Init Ogre";
        GeneLabOgreBullet::OgreManager* ogreEngine = new GeneLabOgreBullet::OgreManager(winId);
        ogreEngine->init();


        this->engines.insert("Ogre", ogreEngine);

        qDebug() << "[OK]\n";

        // camera 1
        Ogre::Camera* cam1 = ogreEngine->getOgreSceneManager()->createCamera("firstCamera");
        cam1->setPosition(Ogre::Vector3(0, 2, 6));
        cam1->lookAt(Ogre::Vector3(0, 2, 0));
        cam1->setNearClipDistance(0.001); // 1 mm
        cam1->setFarClipDistance(100); // 100m

        // camera 2
        // Ogre::Camera* cam2 = graphics->getOgreSceneManager()->createCamera("secondCamera");
        // cam2->setPosition(Ogre::Vector3(0, 18, 0));
        // cam2->lookAt(Ogre::Vector3(0, 0, 70));
        // cam2->setNearClipDistance(5);
        // qDebug() << "[OK]\n";

        // widget 1
        QWidget* oW1 = ogreEngine->createOgreWidget(cam1, sceneWidget);
        this->widgets.insert("OgreWidget", oW1);


        sceneWidget->layout()->addWidget(oW1);
        //this->ui->centralWidget->layout()->addWidget(oW1);

        // widget 2
        // this->ui->centralWidget->layout()->addWidget(oW2);
        // QWidget* oW2 = graphics->createOgreWidget(cam2, this->ui->centralWidget);


        // ----------------------
        // -- Physics : Bullet --
        // ----------------------

        qDebug() << "Init Bullet";
        GeneLabOgreBullet::BulletManager* bulletEngine = new GeneLabOgreBullet::BulletManager();
        bulletEngine->init(ogreEngine);

        this->engines.insert("Bullet", bulletEngine);

        qDebug() << "[OK]\n";


        // ----------------------
        // -- Brain : Neural Network --
        // ----------------------

        qDebug() << "Init Brain Engine";
        GeneLabCore::BrainEngine* brainEngine = new GeneLabCore::BrainEngine();


        this->engines.insert("Brain", brainEngine);

        qDebug() << "[OK]\n";


        // ------------
        // -- Events --
        // ------------
        qDebug() << "Init Events Manager";

        // Events
        GeneLabOgreBullet::EventManager *em = new GeneLabOgreBullet::EventManager();

        CreatureViewerInputManager *cvim = new CreatureViewerInputManager();
        cvim->initOgreBullet(ogreEngine,bulletEngine,cam1);
        em->addListener(cvim);

        connect(oW1,SIGNAL(mousePressed(QMouseEvent*)),em,SLOT(mousePressEvent(QMouseEvent*)));
        connect(oW1,SIGNAL(mouseReleased(QMouseEvent*)),em,SLOT(mouseReleaseEvent(QMouseEvent*)));
        connect(oW1,SIGNAL(mouseMoved(QMouseEvent*)),em,SLOT(mouseMoveEvent(QMouseEvent*)));

        connect(oW1,SIGNAL(keyPressed(QKeyEvent*)),em,SLOT(keyPressEvent(QKeyEvent*)));
        connect(oW1,SIGNAL(keyReleased(QKeyEvent*)),em,SLOT(keyReleaseEvent(QKeyEvent*)));

        connect(oW1,SIGNAL(entered(QEvent*)),em,SLOT(enterViewPortEvent(QEvent*)));
        connect(oW1,SIGNAL(leaved(QEvent*)),em,SLOT(leaveViewPortEvent(QEvent*)));

        this->engines.insert("Event", em);

        qDebug() << "[OK]\n";

    }

    bool MainFactory::create(Ressource r) {

    }

    QMap<QString, GeneLabCore::Engine*>        MainFactory::getEngines() {
        return engines;

    }

    QMap<QString, GeneLabCore::EntityFamily*>  MainFactory::getFamilys() {
        return familys;
    }

    QMap<QString, GeneLabCore::World*>         MainFactory::getWorlds() {
        return worlds;
    }


    QMap<QString, QWidget*>                    MainFactory::getWidgets() {
        return widgets;
    }

    // Vérifie que les dépendances sont assurées
    bool isValid() {
        return true;
    }

    // Dernier message d'erreur
    QString error() {
        return "No error";
    }

}
