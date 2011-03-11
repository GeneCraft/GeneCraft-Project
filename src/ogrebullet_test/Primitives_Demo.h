/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#ifndef _OGREBULLET_Primitives_Demo__H
#define _OGREBULLET_Primitives_Demo__H

#include "OgreBulletDynamics.h"
#include "OgreBulletListener.h"

// -------------------------------------------------------------------------
class Primitives_Demo : public OgreBulletListener 
{
public:

    Primitives_Demo() : OgreBulletListener()
      {
          mName = "Primitives Test Scene";
      };
    virtual ~Primitives_Demo(){};


    void init (Ogre::Root *root, Ogre::RenderWindow *win, OgreBulletApplication *application);



   void keyPressed(BULLET_KEY_CODE key);
};


#endif //_OGREBULLET_Primitives_Demo__H
