/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#ifndef _OGREBULLET_Trimesh_Demo__H
#define _OGREBULLET_Trimesh_Demo__H

#include "OgreBulletDynamics.h"
#include "OgreBulletListener.h"

// -------------------------------------------------------------------------
class Trimesh_Demo : public OgreBulletListener 
{
public:

    Trimesh_Demo() : OgreBulletListener()
      {
          mName = "Trimesh Static Scene test";
      };
    virtual ~Trimesh_Demo(){};


    void init(Ogre::Root *root, Ogre::RenderWindow *win, OgreBulletApplication *application);

    void keyPressed(BULLET_KEY_CODE key);


};


#endif //_OGREBULLET_Trimesh_Demo__H
