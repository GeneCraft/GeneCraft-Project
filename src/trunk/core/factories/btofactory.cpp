#include "btofactory.h"

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
#include "btoshapesfactory.h"

namespace GeneCraftCore {
btoFactory::btoFactory(QWidget* sceneWidget, unsigned long winId, QObject *parent) :
    btFactory(parent)
{

    // ---------------------
    // -- Graphics : Ogre --
    // ---------------------

    // Cration des diffrents engines
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
    ogreEngine->initOverlay();

    this->engines.insert("Ogre", ogreEngine);


    // widget 1
    qDebug() << "[OK]\n";

    // ----------------------------
    // -- Bullet and Ogre linker --
    // ----------------------------
    qDebug() << "Bullet and Ogre linker";
    BulletOgreEngine* bulletOgreEngine = new BulletOgreEngine((BulletEngine*)engines.find("Bullet").value(),ogreEngine);
    this->engines.insert("BulletOgre", bulletOgreEngine);
    qDebug() << "[OK]\n";

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
}
