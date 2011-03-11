/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#include "OgreBulletListener.h"
#include "OgreBulletGuiListener.h"

using namespace Ogre;

// -------------------------------------------------------------------------
OgreBulletGuiListener::OgreBulletGuiListener(OgreBulletListener *listener, Ogre::RenderWindow *win) :
    mListener(listener),
    mWindow(win),
    mMouseOverlay(0),
    mMousePanel(0)
{	
        
    /******************* CREATE Cursor Overlay ***************************/
    mMouseOverlay = (Overlay*)OverlayManager::getSingleton().getByName("GuiOverlay");
    if (mMouseOverlay)
    {
        mMousePanel = OverlayManager::getSingleton().getOverlayElement ("GUIMouse");
    }
    else
    {
        mMouseOverlay = OverlayManager::getSingletonPtr()->create("GuiOverlay");
        mMouseOverlay->setZOrder(600);
        mMousePanel = (Ogre::OverlayElement *)
            OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIMouse");
        mMousePanel->setMaterialName("OgreBulletDemos/TargetSights");

        TexturePtr mouseTex = TextureManager::getSingleton().load("target.png", "Bullet");
        mMousePanel->setWidth (mouseTex->getWidth() / (float)win->getWidth());
        mMousePanel->setHeight (mouseTex->getHeight() / (float)win->getHeight());

        Ogre::OverlayContainer		*mouseContainer = (Ogre::OverlayContainer*) 
            OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIContainer");
        mMouseOverlay->add2D(mouseContainer);
        mouseContainer->addChild(mMousePanel);
    }

    mMouseOverlay->show(); 
    TexturePtr mouseTex = TextureManager::getSingleton().load("target.png", "Bullet");
    mMouseCursorHalfWidth = (Real(mouseTex->getWidth()) / mWindow->getWidth()) * 0.5;
    mMouseCursorHalfHeight = (Real(mouseTex->getHeight())  / mWindow->getHeight ()) * 0.5;

    /******************* CREATE GUI ***************************/
    mGui = new BetaGUI::GUI("OgreBulletGui", "BlueHighway", 14, win);
    OverlayContainer* mouseCursor = mGui->createMousePointer(Vector2(32, 32), "bgui.pointer");
    mouseCursor->hide();

    mGui->injectMouse(mWindow->getWidth() * 0.5, mWindow->getHeight() * 0.5, false);

}
// -------------------------------------------------------------------------
OgreBulletGuiListener::~OgreBulletGuiListener()
{
    // other buttons  and window managed by BETAGUI will be deleted by BETAGUI himself.
    delete mGui;
}
// -------------------------------------------------------------------------
void OgreBulletGuiListener::addBool(BetaGUI::Window *window, bool* value, const String &label, Vector2 &pos)
{
    window->createBoolButton(
        Vector4(pos.x, pos.y, 7*label.size(), 24), 
        "bgui.button", 
        label, 
        BetaGUI::Callback(this), 
        value);
}
// -------------------------------------------------------------------------
void OgreBulletGuiListener::onButtonPress(BetaGUI::Button *ref, Ogre::uchar type)
{
    //if(type == 1) // button down
    //{
        //      
    //}
}
// -------------------------------------------------------------------------
void OgreBulletGuiListener::hideMouse()
{
   mMousePanel->hide();
}
// -------------------------------------------------------------------------
void OgreBulletGuiListener::showMouse()
{
   mMousePanel->show();
}
// -------------------------------------------------------------------------
void OgreBulletGuiListener::setMousePosition(Ogre::Real x, Ogre::Real y)
{
    mMousePanel->setPosition (x - mMouseCursorHalfWidth, y - mMouseCursorHalfHeight);
}