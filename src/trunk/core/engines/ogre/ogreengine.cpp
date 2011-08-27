#include "ogreengine.h"
#include "Ogre.h"
#include <QDebug>
#include <QApplication>
#include "ogrewidget.h"


#include "Ogre.h"
#include "OgreTextAreaOverlayElement.h"

namespace GeneCraftCore {

    // We use genelab core for code productivity
    using namespace GeneCraftCore;

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
        //this->initOverlay();
    }

    Ogre::Root* OgreEngine::getOgreRoot() {
        return ogreRoot;
    }

    void OgreEngine::initOgreRoot() {
        ogreRoot = new Ogre::Root();
        bool reload = ogreRoot->restoreConfig();
        if(!reload) {
            bool ok = ogreRoot->showConfigDialog();
            if(!ok)
                QApplication::exit(-1);
        }

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
    }

    void OgreEngine::initOverlay() {

        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelName"));
            panel->setMetricsMode(Ogre::GMM_PIXELS);
            panel->setPosition(10, 10);
            panel->setDimensions(100, 100);

            Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
            overlayManager.createOverlayElement("TextArea", "worldName"));
            textArea->setMetricsMode(Ogre::GMM_PIXELS);
            textArea->setPosition(10, 10);
            textArea->setDimensions(100, 200);
            textArea->setFontName("StarWars");
            //textArea->setCaption(this->data["name"].toString().toStdString());
            textArea->setCharHeight(16);
            textArea->setColourBottom(Ogre::ColourValue(1, 1, 1));
            textArea->setColourTop(Ogre::ColourValue(1, 1, 1));

            Ogre::TextAreaOverlayElement* textArea2 = static_cast<Ogre::TextAreaOverlayElement*>(
            overlayManager.createOverlayElement("TextArea", "timeArea"));
            textArea2->setMetricsMode(Ogre::GMM_PIXELS);
            textArea2->setPosition(10, 30);
            textArea2->setDimensions(100, 200);
            textArea2->setFontName("StarWars");
            textArea2->setCaption("0min 0sec");
            textArea2->setCharHeight(16);
            textArea2->setColourBottom(Ogre::ColourValue(1, 1, 1));
            textArea2->setColourTop(Ogre::ColourValue(1, 1, 1));

            Ogre::Overlay* overlay = overlayManager.create("OverlayName");
            overlay->add2D(panel);
            panel->addChild(textArea);
            panel->addChild(textArea2);
            overlay->show();
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
