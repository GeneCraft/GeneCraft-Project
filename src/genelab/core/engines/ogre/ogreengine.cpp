#include "ogreengine.h"
#include "Ogre.h"
#include <QDebug>
#include <QApplication>
#include "ogrewidget.h"

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

    void OgreEngine::initRenderingSystem(unsigned long winId) {
        // Get the parameters of the window QT created
        /*
        //Parameters to pass to Ogre::Root::createRenderWindow()
        Ogre::NameValuePairList params;
        //params["useNVPerfHUD"] = "true";

        //The external windows handle parameters are platform-specific
        Ogre::String externalWindowHandleParams;

        //Accept input focus
        //setFocusPolicy(Qt::StrongFocus);

#if defined(Q_WS_WIN) || defined(Q_WS_MAC)
        //positive integer for W32 (HWND handle) - According to Ogre Docs
        externalWindowHandleParams = Ogre::StringConverter::toString((unsigned int)(winId));
#endif

#if defined(Q_WS_X11)
        //poslong:posint:poslong:poslong (display*:screen:windowHandle:XVisualInfo*) for GLX - According to Ogre Docs
        QX11Info info = x11Info();
        externalWindowHandleParams  = Ogre::StringConverter::toString((unsigned long)(info.display()));
        externalWindowHandleParams += ":";
        externalWindowHandleParams += Ogre::StringConverter::toString((unsigned int)(info.screen()));
        externalWindowHandleParams += ":";
        externalWindowHandleParams += Ogre::StringConverter::toString((unsigned long)(winId()));
        //externalWindowHandleParams += ":";
        //externalWindowHandleParams += Ogre::StringConverter::toString((unsigned long)(info.visual()));
#endif

        //Add the external window handle parameters to the existing params set.
#if defined(Q_WS_WIN) || defined(Q_WS_MAC)
        params["parentWindowHandle"] = externalWindowHandleParams;
#endif

#if defined(Q_WS_X11)
        params["parentWindowHandle"] = externalWindowHandleParams;
#endif

#if defined(Q_WS_MAC)
        params["macAPI"] = "cocoa";
        //params["macAPICocoaUseNSView"] = "true";
#endif
         //Finally create our window.
        Ogre::RenderWindow* mOgreWindow = this->ogreRoot->createRenderWindow(
                "FakeOne",
                640, 480, false, &params);

        mOgreWindow->setActive(false);
        mOgreWindow->setVisible(false);
        //mOgreWindow->destroy();*/

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
