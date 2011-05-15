#include "ogremanager.h"
#include "OGRE/Ogre.h"
#include <QDebug>
#include <QApplication>
#include "ui/widget/ogrewidget.h"

namespace GeneLabCore {

    // We use genelab core for code productivity
    using namespace GeneLabCore;

    OgreManager::OgreManager(unsigned long winId) :
        Engine()
    {
        this->winId = winId;
    }

    void OgreManager::init() {
        this->initOgreRoot();
        this->initRenderingSystem(winId);
        this->initResources();
        this->initSceneManager();

    }

    Ogre::Root* OgreManager::getOgreRoot() {
        return ogreRoot;
    }

    void OgreManager::initOgreRoot() {
        ogreRoot = new Ogre::Root();
        bool ok = ogreRoot->showConfigDialog();
        if(!ok)
            QApplication::exit(-1);

        ogreRoot->getRenderSystem()->setConfigOption( "Full Screen", "No" );
        ogreRoot->saveConfig();
        ogreRoot->initialise(false); // don't create a window
    }

    void OgreManager::initRenderingSystem(unsigned long winId) {
        // Get the parameters of the window QT created
        Ogre::String winHandle;
        #ifdef WIN32
        // Windows code
        winHandle += Ogre::StringConverter::toString(winId);
        #else
        // Unix code
        QX11Info info = x11Info();
        winHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
        winHandle += ":";
        winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
        winHandle += ":";
        winHandle += Ogre::StringConverter::toString(winId);
        #endif

        Ogre::NameValuePairList params;
        params["parentWindowHandle"] = winHandle;

        fakeRender = ogreRoot->createRenderWindow( "fakewindow",
                                 640,
                                 480,
                                 false,
                                 &params );

        fakeRender->setActive(false);
        fakeRender->setVisible(false);
    }

    void OgreManager::initResources() {
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

    void OgreManager::initSceneManager() {
        //== Ogre Initialization ==//
        qDebug() << "ogre ok";
        Ogre::SceneType scene_manager_type = Ogre::ST_INTERIOR;

        scnManager = ogreRoot->createSceneManager( scene_manager_type );
    }

    OgreWidget* OgreManager::createOgreWidget(Ogre::Camera* cam, QWidget* parent) {

        OgreWidget* ow = new OgreWidget(ogreRoot, scnManager, cam, parent);
        ow->init();

        ogreWidgets.append(ow);

        return ow;
    }

    Ogre::SceneManager* OgreManager::getOgreSceneManager() {
        return this->scnManager;
    }

    void OgreManager::beforeStep() {

    }

    void OgreManager::afterStep() {

    }

    void OgreManager::step() {

        ogreRoot->renderOneFrame();

        for(int i = 0; i < ogreWidgets.size(); i++) {

            ogreWidgets[i]->step();

            if(ogreWidgets[i]->resized)
                ogreWidgets[i]->resize();
        }
    }
}
