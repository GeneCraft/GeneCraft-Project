/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)

This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#include "TriMesh_Demo.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#if !(OGRE_VERSION <  ((1 << 16) | (3 << 8) | 0))
using namespace OIS;
#endif 

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

// -------------------------------------------------------------------------
const Ogre::Vector3    CameraStart            = Ogre::Vector3(0,-9,1);
// -------------------------------------------------------------------------


// -------------------------------------------------------------------------
void Trimesh_Demo::init(Ogre::Root *root, Ogre::RenderWindow *win, OgreBulletApplication *application)
{
    mHelpKeys.clear();
    mHelpKeys.push_back (BASIC_HELP_INFO0);
    mHelpKeys.push_back (BASIC_HELP_INFO1);
    mHelpKeys.push_back (BASIC_HELP_INFO2);
    mHelpKeys.push_back (BASIC_HELP_INFO3);
    mHelpKeys.push_back (BASIC_HELP_INFO4);
    mHelpKeys.push_back (BASIC_HELP_INFO5);
    mHelpKeys.push_back (BASIC_HELP_INFO6);

    // ------------------------
    // Start OgreScene
    mSceneMgr = root->createSceneManager(ST_GENERIC);

    mCamera = mSceneMgr->createCamera("Cam");
    mCamera->setFOVy(Degree(90));
    mCamera->setNearClipDistance(0.1);
    mCamera->setFarClipDistance(100);
    Viewport *vp = win->addViewport(mCamera);
    vp->setBackgroundColour(ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    mCamera->setPosition(CameraStart);
    mCamera->rotate(Ogre::Vector3(1,0,0), Degree(90));
    mCamera->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);


    OgreBulletListener::init(root, win, application);

    // ------------------------
    // add lights
    //setBasicLight();

    // Set ambient light
    mSceneMgr->setAmbientLight(ColourValue(0.75, 0.75, 0.75));

    mSunLight = mSceneMgr->createLight("Sun");
    mSunLight->setPosition(CameraStart + Ogre::Vector3(0,0,15));
    mSunLight->setType(Light::LT_DIRECTIONAL);
    mSunLight->setDirection(-0.40824828, -0.40824828, -0.81649655);
    mSunLight->setCastShadows(true);
    mSunLight->setSpecularColour(0.5,0.5,0.3);

    mLight = mSceneMgr->createLight("Spot");
    mLight->setPosition(CameraStart + Ogre::Vector3(0,0,15));
    mLight->setType(Light::LT_SPOTLIGHT);
    mLight->setDirection(-0.40824828, -0.40824828, -0.81649655);
    mLight->setCastShadows(true);
    mLight->setSpecularColour(0.5,0.5,0.3);
    

    // ------------------------
    // Add the Gui
    setPhysicGUI();

    // ------------------------
    // Start Bullet
    initWorld(Ogre::Vector3 (0, 0, -9.81));

    // ------------------------
    // Add the trimesh
    addStaticTrimesh("sceneMesh",
        "RoomComplex.mesh",
        Ogre::Vector3(0,0,19), 
        Quaternion::IDENTITY,
        0.1f, 
        0.8f);   
}
// -------------------------------------------------------------------------
void Trimesh_Demo::keyPressed(BULLET_KEY_CODE key)
{
    OgreBulletListener::throwDynamicObject (key);
    OgreBulletListener::dropDynamicObject (key);

    return OgreBulletListener::keyPressed (key);
}

