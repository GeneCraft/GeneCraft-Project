/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
/*
GuiListener.h
-------------
A basic test framework that minimize code in each test scene listener.
*/
#ifndef _OgreBulletGuiListener_H_
#define _OgreBulletGuiListener_H_

// We'll need the OgreBulletListener definitions
#include "BetaGUI.h"

class OgreBulletListener;

/*
The base Test class, is also able to listen for collisions and thus change the contact properties
*/
class OgreBulletGuiListener : public BetaGUI::BetaGUIListener
{
public:
	// Constructor/destructor
    OgreBulletGuiListener(OgreBulletListener *listener, Ogre::RenderWindow *win);
    virtual ~OgreBulletGuiListener();

    // Gui Callbacks
    void onButtonPress(BetaGUI::Button *ref, Ogre::uchar type);


    BetaGUI::GUI *getGui(){return mGui;}

    void addBool(BetaGUI::Window *mainWindow, bool* value, const Ogre::String &label, Ogre::Vector2 &pos);

    void hideMouse();
    void showMouse();
    void setMousePosition(Ogre::Real x, Ogre::Real y);
    
    void showHelp(bool show);
protected:

   BetaGUI::GUI *mGui;

   OgreBulletListener *mListener;
   Ogre::RenderWindow *mWindow;


   Ogre::Overlay		    *mMouseOverlay;
   Ogre::OverlayElement		*mMousePanel;
   Ogre::Real              mMouseCursorHalfWidth;
   Ogre::Real              mMouseCursorHalfHeight;

};

#endif

