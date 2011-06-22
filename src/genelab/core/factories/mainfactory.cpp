#include "mainfactory.h"

// Qt
#include <QDebug>
#include <QVBoxLayout>

#include "Ogre.h"
#include "ogre/ogreengine.h"
#include "ogre/ogrewidget.h"
#include "bullet/bulletengine.h"
#include "bulletogre/bulletogreengine.h"
#include "events/eventsmanager.h"
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
        ogreEngine->initOgreRoot();
        ogreEngine->initSceneManager();

        // camera 1

        QWidget* oW1 = ogreEngine->createOgreWidget("MainWidget", NULL, sceneWidget);
        this->widgets.insert("OgreWidget", oW1);

        if(sceneWidget->layout() == NULL)
           sceneWidget->setLayout(new QVBoxLayout(sceneWidget));

        sceneWidget->layout()->addWidget(oW1);

        ogreEngine->initResources();

        this->engines.insert("Ogre", ogreEngine);



        // camera 2
        // Ogre::Camera* cam2 = graphics->getOgreSceneManager()->createCamera("secondCamera");
        // cam2->setPosition(Ogre::Vector3(0, 18, 0));
        // cam2->lookAt(Ogre::Vector3(0, 0, 70));
        // cam2->setNearClipDistance(5);
        // qDebug() << "[OK]\n";

        // widget 1
        qDebug() << "[OK]\n";
        //this->ui->centralWidget->layout()->addWidget(oW1);

        // widget 2
        // this->ui->centralWidget->layout()->addWidget(oW2);
        // QWidget* oW2 = graphics->createOgreWidget("SecondWidget",cam2, this->ui->centralWidget);


        // ----------------------
        // -- Physics : Bullet --
        // ----------------------
        qDebug() << "Init Bullet";
        BulletEngine* bulletEngine = new BulletEngine();
        this->engines.insert("Bullet", bulletEngine);
        qDebug() << "[OK]\n";


        // ----------------------------
        // -- Bullet and Ogre linker --
        // ----------------------------
        qDebug() << "Bullet and Ogre linker";
        BulletOgreEngine* bulletOgreEngine = new BulletOgreEngine(bulletEngine,ogreEngine);
        this->engines.insert("BulletOgre", bulletOgreEngine);
        qDebug() << "[OK]\n";

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
        //qDebug() << "World creation";
        //World *world = new OgreBulletWorld(this);
        //world->setup();
        //this->worlds.insert("BasicWorld", world);
        //qDebug() << "[OK]\n";

        // ------------
        // -- Events --
        // ------------
        qDebug() << "Init Events Manager";
        EventsManager *em = new EventsManager();
        connect(oW1,SIGNAL(mousePressed(QMouseEvent*)),em,SLOT(mousePressEvent(QMouseEvent*)));
        connect(oW1,SIGNAL(mouseReleased(QMouseEvent*)),em,SLOT(mouseReleaseEvent(QMouseEvent*)));
        connect(oW1,SIGNAL(mouseMoved(QMouseEvent*)),em,SLOT(mouseMoveEvent(QMouseEvent*)));
        connect(oW1,SIGNAL(keyPressed(QKeyEvent*)),em,SLOT(keyPressEvent(QKeyEvent*)));
        connect(oW1,SIGNAL(keyReleased(QKeyEvent*)),em,SLOT(keyReleaseEvent(QKeyEvent*)));
        connect(oW1,SIGNAL(entered(QEvent*)),em,SLOT(enterViewPortEvent(QEvent*)));
        connect(oW1,SIGNAL(leaved(QEvent*)),em,SLOT(leaveViewPortEvent(QEvent*)));
        this->engines.insert("Events", em);
        qDebug() << "[OK]\n";
    }

    bool MainFactory::create(Ressource* r) {
        return true;
    }

    QMap<QString, Engine*> MainFactory::getEngines() {
        return QMap<QString, Engine*>(engines);

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

    /*btShapesFactory* MainFactory::getShapesFactory()
    {
        return shapesFactory;
    }*/

    // Vérifie que les dépendances sont assurées
    bool isValid() {
        return true;
    }

    // Dernier message d'erreur
    QString error() {
        return "No error";
    }

}
