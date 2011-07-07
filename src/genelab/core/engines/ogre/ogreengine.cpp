#include "ogreengine.h"
#include "Ogre.h"
#include <QDebug>
#include <QApplication>
#include "ogrewidget.h"


#include "Ogre.h"
#include "OgreTextAreaOverlayElement.h"

namespace GeneLabCore {

    // We use genelab core for code productivity
    using namespace GeneLabCore;

    OgreEngine::OgreEngine(unsigned long winId) :
        Engine()
    {
        this->winId = winId;
    }

    void OgreEngine::init() {
        this->initOgreRoot();
        this->initRenderingSystem(winId);
        this->initResources();
        this->initSceneManager();
    }

    Ogre::Root* OgreEngine::getOgreRoot() {
        return ogreRoot;
    }

    void OgreEngine::initOgreRoot() {
        ogreRoot = new Ogre::Root();
        bool ok = ogreRoot->showConfigDialog();
        if(!ok)
            QApplication::exit(-1);

        ogreRoot->getRenderSystem()->setConfigOption( "Full Screen", "No" );
        ogreRoot->saveConfig();
        ogreRoot->initialise(false); // don't create a window
    }

    void OgreEngine::initRenderingSystem(unsigned long) {

    }

    void OgreEngine::initResources() {
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

    void OgreEngine::initSceneManager() {
        //== Ogre Initialization ==//
        Ogre::SceneType scene_manager_type = Ogre::ST_GENERIC;

        scnManager = ogreRoot->createSceneManager( scene_manager_type );
        qDebug() << scnManager << "scn manager inited !";
    }

    OgreWidget* OgreEngine::createOgreWidget(QString widgetName, Ogre::Camera* cam, QWidget* parent) {

        OgreWidget* ow = new OgreWidget(ogreRoot, scnManager, cam, parent);
        ow->init();

        ogreWidgets.insert(widgetName,ow);

        return ow;
    }

    OgreWidget * OgreEngine::getOgreWidget(QString widgetName)
    {
        return ogreWidgets.find(widgetName).value();
    }

    Ogre::SceneManager* OgreEngine::getOgreSceneManager() {
        return this->scnManager;
    }

    void OgreEngine::beforeStep() {

    }

    void OgreEngine::afterStep() {

    }

    void OgreEngine::step() {
        ogreRoot->renderOneFrame();

        foreach(OgreWidget *ow, ogreWidgets)
        {
            ow->step();

            if(ow->resized)
                ow->resize();
        }
    }
}
