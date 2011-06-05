#include "mainfactory.h"

// Qt
#include <QDebug>
#include <QVBoxLayout>

#include "OGRE/Ogre.h"
#include "ogre/ogreengine.h"
#include "ogre/ogrewidget.h"
#include "bullet/bulletengine.h"
#include "bulletogre/bulletogreengine.h"
#include "events/eventmanager.h"
#include "creatureviewerinputmanager.h"
#include "ressources/ressource.h"

#include "entities/entitiesengine.h"
#include "world/ogrebulletworld.h"
#include "world/world.h"
#include "btoshapesfactory.h"

namespace GeneLabCore {

    MainFactory::MainFactory(QWidget* sceneWidget, unsigned long winId, QObject *parent) :
        QObject(parent)
    {

        // ---------------------
        // -- Graphics : Ogre --
        // ---------------------

        // Création des différents engines
        qDebug() << "Init Ogre";
        OgreEngine* ogreEngine = new OgreEngine(winId);
        ogreEngine->init();

        this->engines.insert("Ogre", ogreEngine);

        qDebug() << "[OK]\n";

        // camera 1
        Ogre::Camera* cam1 = ogreEngine->getOgreSceneManager()->createCamera("firstCamera");
        cam1->setPosition(Ogre::Vector3(0, 2, 6));
        cam1->lookAt(Ogre::Vector3(0, 2, 0));
        cam1->setNearClipDistance(0.01); // 10 mm
        cam1->setFarClipDistance(5000); // 1km

        // camera 2
        // Ogre::Camera* cam2 = graphics->getOgreSceneManager()->createCamera("secondCamera");
        // cam2->setPosition(Ogre::Vector3(0, 18, 0));
        // cam2->lookAt(Ogre::Vector3(0, 0, 70));
        // cam2->setNearClipDistance(5);
        // qDebug() << "[OK]\n";

        // widget 1
        QWidget* oW1 = ogreEngine->createOgreWidget("MainWidget",cam1, sceneWidget);
        this->widgets.insert("OgreWidget", oW1);

        if(sceneWidget->layout() == NULL)
           sceneWidget->setLayout(new QVBoxLayout(sceneWidget));

        sceneWidget->layout()->addWidget(oW1);

        //this->ui->centralWidget->layout()->addWidget(oW1);

        // widget 2
        // this->ui->centralWidget->layout()->addWidget(oW2);
        // QWidget* oW2 = graphics->createOgreWidget("SecondWidget",cam2, this->ui->centralWidget);


        // ----------------------
        // -- Physics : Bullet --
        // ----------------------
        qDebug() << "Init Bullet";
        BulletEngine* bulletEngine = new BulletEngine();
        bulletEngine->init();
        this->engines.insert("Bullet", bulletEngine);
        qDebug() << "[OK]\n";


        // ----------------------------
        // -- Bullet and Ogre linker --
        // ----------------------------
        qDebug() << "Bullet and Ogre linker";
        BulletOgreEngine* bulletOgreEngine = new BulletOgreEngine(bulletEngine,ogreEngine);
        this->engines.insert("BulletOgre", bulletOgreEngine);
        qDebug() << "[OK]\n";

        // --------------------
        // -- Shapes Factory --
        // --------------------
        shapesFactory = new btoShapesFactory(bulletOgreEngine);

        // ---------------------
        // -- Entities engine --
        // ---------------------
        qDebug() << "Init Entities Engine";
        EntitiesEngine* entitiesEngine = new EntitiesEngine();
        this->engines.insert("Entities", entitiesEngine);
        qDebug() << "[OK]\n";

        // ---------------------
        // -- Scene (Content) --
        // ---------------------
        qDebug() << "World creation";
        World *world = new OgreBulletWorld(this);
        world->setup();
        this->worlds.insert("BasicWorld", world);
        qDebug() << "[OK]\n";

        // ------------
        // -- Events --
        // ------------
        qDebug() << "Init Events Manager";
        EventManager *em = new EventManager();
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

    bool MainFactory::create(Ressource* r) {
        return true;
    }

    QMap<QString, Engine*> MainFactory::getEngines() {
        return engines;

    }

    QMap<QString, EntityFamily*> MainFactory::getFamilys() {
        return familys;
    }

    QMap<QString, World*> MainFactory::getWorlds() {
        return worlds;
    }


    QMap<QString, QWidget*> MainFactory::getWidgets() {
        return widgets;
    }

    btShapesFactory* MainFactory::getShapesFactory()
    {
        return shapesFactory;
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
