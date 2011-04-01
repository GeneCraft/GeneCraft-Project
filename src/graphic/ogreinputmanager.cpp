#include "ogreinputmanager.h"

OgreInputManager::OgreInputManager(QObject *parent) :
    QObject(parent)
{

}


//-------------------------------------------------------------------------------------
bool OgreInputManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
//    if(mWindow->isClosed())
//        return false;

//    if(mShutDown)
//        return false;

//    //Need to capture/update each device
//    mKeyboard->capture();
//    mMouse->capture();

//    mTrayMgr->frameRenderingQueued(evt);

//    if (!mTrayMgr->isDialogVisible())
//    {
//        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
//        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
//        {
//            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
//            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
//            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
//            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
//            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
//            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
//            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
//        }
//    }

    return true;
}
//-------------------------------------------------------------------------------------
bool OgreInputManager::keyPressed( const OIS::KeyEvent &arg )
{
//    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

//    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
//    {
//        mTrayMgr->toggleAdvancedFrameStats();
//    }
//    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
//    {
//        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
//        {
//            mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
//            mDetailsPanel->show();
//        }
//        else
//        {
//            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
//            mDetailsPanel->hide();
//        }
//    }
//    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
//    {
//        Ogre::String newVal;
//        Ogre::TextureFilterOptions tfo;
//        unsigned int aniso;

//        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
//        {
//        case 'B':
//            newVal = "Trilinear";
//            tfo = Ogre::TFO_TRILINEAR;
//            aniso = 1;
//            break;
//        case 'T':
//            newVal = "Anisotropic";
//            tfo = Ogre::TFO_ANISOTROPIC;
//            aniso = 8;
//            break;
//        case 'A':
//            newVal = "None";
//            tfo = Ogre::TFO_NONE;
//            aniso = 1;
//            break;
//        default:
//            newVal = "Bilinear";
//            tfo = Ogre::TFO_BILINEAR;
//            aniso = 1;
//        }

//        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
//        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
//        mDetailsPanel->setParamValue(9, newVal);
//    }
//    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
//    {
//        Ogre::String newVal;
//        Ogre::PolygonMode pm;

//        switch (mCamera->getPolygonMode())
//        {
//        case Ogre::PM_SOLID:
//            newVal = "Wireframe";
//            pm = Ogre::PM_WIREFRAME;
//            break;
//        case Ogre::PM_WIREFRAME:
//            newVal = "Points";
//            pm = Ogre::PM_POINTS;
//            break;
//        default:
//            newVal = "Solid";
//            pm = Ogre::PM_SOLID;
//        }

//        mCamera->setPolygonMode(pm);
//        mDetailsPanel->setParamValue(10, newVal);
//    }
//    else if(arg.key == OIS::KC_F5)   // refresh all textures
//    {
//        Ogre::TextureManager::getSingleton().reloadAll();
//    }
//    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
//    {
//        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
//    }
//    else if (arg.key == OIS::KC_ESCAPE)
//    {
//        mShutDown = true;
//    }

//    mCameraMan->injectKeyDown(arg);
      return true;
}

bool OgreInputManager::keyReleased( const OIS::KeyEvent &arg )
{
//    mCameraMan->injectKeyUp(arg);
      return true;
}

bool OgreInputManager::mouseMoved( const OIS::MouseEvent &arg )
{
//    if (mTrayMgr->injectMouseMove(arg)) return true;
//    mCameraMan->injectMouseMove(arg);
      return true;
}

bool OgreInputManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
//    if (mTrayMgr->injectMouseDown(arg, id)) return true;
//    mCameraMan->injectMouseDown(arg, id);
      return true;
}

bool OgreInputManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
//    if (mTrayMgr->injectMouseUp(arg, id)) return true;
//    mCameraMan->injectMouseUp(arg, id);
      return true;
}
