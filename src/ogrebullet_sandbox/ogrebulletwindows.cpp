#include "ogrebulletwindows.h"
#include "ui_ogrebulletwindows.h"
#include "graphic/ogrewidget.h"
#include "OGRE/Ogre.h"
#include <QDebug>

void OgreBulletWindows::initRenderingSystem(Ogre::Root *ogreRoot) {
    // Get the parameters of the window QT created
    Ogre::String winHandle;
    #ifdef WIN32
    // Windows code
    winHandle += Ogre::StringConverter::toString((unsigned long)(this->winId()));
    #else
    // Unix code
    QX11Info info = x11Info();
    winHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
    winHandle += ":";
    winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
    winHandle += ":";
    winHandle += Ogre::StringConverter::toString((unsigned long)(this->winId()));
    #endif

    Ogre::NameValuePairList params;
    params["parentWindowHandle"] = winHandle;

    Ogre::RenderWindow* fakeWindow = ogreRoot->createRenderWindow( "fakewindow",
                             640,
                             480,
                             false,
                             &params );

    fakeWindow->setActive(false);
    fakeWindow->setVisible(false);
}

Ogre::Root* OgreBulletWindows::initOgreRoot() {
    ogreRoot = new Ogre::Root();
    bool ok = ogreRoot->showConfigDialog();
    if(!ok)
        QApplication::exit(-1);

    ogreRoot->getRenderSystem()->setConfigOption( "Full Screen", "No" );
    ogreRoot->saveConfig();
    ogreRoot->initialise(false); // don't create a window
    return ogreRoot;
}

void OgreBulletWindows::initResources() {
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load("resources.cfg");

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

Ogre::SceneManager* OgreBulletWindows::initSceneManager(Ogre::Root* ogreRoot) {
    //== Ogre Initialization ==//
    qDebug() << "ogre ok";
    Ogre::SceneType scene_manager_type = Ogre::ST_INTERIOR;

    Ogre::SceneManager* sceneMgr = ogreRoot->createSceneManager( scene_manager_type );
    return sceneMgr;
}

void OgreBulletWindows::createScene(Ogre::SceneManager *mSceneMgr) {

    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    Ogre::Entity* entNinja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
    entNinja->setCastShadows(true);
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);

    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 150, 250));

    pointLight->setDiffuseColour(1.0, 0.0, 0.0);
    pointLight->setSpecularColour(1.0, 0.0, 0.0);

    Ogre::Light* directionalLight = mSceneMgr->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));

    directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));

    Ogre::Light* spotLight = mSceneMgr->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);

    spotLight->setDirection(-1, -1, 0);
    spotLight->setPosition(Ogre::Vector3(300, 300, 0));

    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
}

OgreBulletWindows::OgreBulletWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OgreBulletWindows)
{
    ui->setupUi(this);

    Ogre::Root* ogreRoot = this->initOgreRoot();
    this->initRenderingSystem(ogreRoot);
    this->initResources();
    Ogre::SceneManager* sceneMgr = this->initSceneManager(ogreRoot);

    qDebug() << "scenemanager ok";
    Ogre::Camera* camera = sceneMgr->createCamera( "QOgreWidget_Cam" );
    /*camera->setPosition( Ogre::Vector3(0,1,0) );
    camera->lookAt( Ogre::Vector3(0,0,0) );
    camera->setNearClipDistance( 1.0 );*/
    // Position it at 500 in Z direction
    camera->setPosition(Ogre::Vector3(0,250,500));
    camera->lookAt(Ogre::Vector3(0,0,-500));
    // set the near clip distance
    camera->setNearClipDistance(5);
//    camera->setFarClipDistance(1000);

/*
    Ogre::Camera* camera2 = sceneMgr->createCamera( "QOgreWidget_Cam2" );

    // Position it at 500 in Z direction
    camera2->setPosition(Ogre::Vector3(500,250,0));
    // Look back along -Z
    camera2->lookAt(Ogre::Vector3(0,0,0));
    camera2->setNearClipDistance(5);
    */
//    camera2->setFarClipDistance(1000);

    this->createScene(sceneMgr);

    qDebug() << "camera ok";
    oW1 = new OgreWidget(ogreRoot, sceneMgr, camera, this->ui->centralWidget);
    this->ui->centralWidget->layout()->addWidget(oW1);
    oW1->init();


    oW2 = new OgreWidget(ogreRoot, sceneMgr, camera, this->ui->centralWidget);
    this->ui->centralWidget->layout()->addWidget(oW2);
    oW2->init();

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

   ogreRoot->renderOneFrame();

   if(oW1->resized)
       oW1->resize();
   if(oW2->resized)
       oW2->resize();
}
