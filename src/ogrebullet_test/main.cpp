/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/

#include "OgreBulletApplication.h"
#include "Primitives_Demo.h"
#include "Constraints_Demo.h"
#include "Vehicle_Demo.h"
#include "TriMesh_Demo.h"
#include "Constraints_Demo.h"
#include "Terrain_Demo.h"
#include "Ragdoll_Demo.h"

// Windows stuff
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

/*
Windows entry point
*/
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT nCmdShow)
#else
int main(int argc,char* argv[])
#endif

{
    std::vector<OgreBulletListener *> ogrebulletscenes;
    std::vector <OgreBulletListener *>::iterator it;

    ogrebulletscenes.push_back(new Primitives_Demo());
    ogrebulletscenes.push_back(new Trimesh_Demo());
    ogrebulletscenes.push_back(new Vehicles_Demo());
    ogrebulletscenes.push_back(new Constraints_Demo());
    ogrebulletscenes.push_back(new Terrain_Demo());
    ogrebulletscenes.push_back(new Ragdoll_Demo());
    ogrebulletscenes.push_back(new Constraints_Demo());

    ogrebulletscenes[0]->setNextKey(KC_F1);
    ogrebulletscenes[1]->setNextKey(KC_F2);
    ogrebulletscenes[2]->setNextKey(KC_F3);
    ogrebulletscenes[3]->setNextKey(KC_F4);
    ogrebulletscenes[4]->setNextKey(KC_F5);
    ogrebulletscenes[5]->setNextKey(KC_F6);

    // Create the application and try to run it
    OgreBulletApplication app(&ogrebulletscenes);

#if (OGRE_VERSION <  ((1 << 16) | (3 << 8) | 0))
    SET_TERM_HANDLER;
#endif 

    try
    {
        app.go();
    } 
    catch(Ogre::Exception& e)
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        //MessageBox( 0, e.getFullDescription().c_str(), "OgreBullet OgreBulletListener: Exception", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
#endif
    }

    it =  ogrebulletscenes.begin();
    while (it != ogrebulletscenes.end())
    {
        delete *it;
        ++it;
    }

    return 0;
}

