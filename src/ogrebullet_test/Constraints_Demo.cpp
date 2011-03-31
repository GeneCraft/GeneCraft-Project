/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#include "Constraints_Demo.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"
#include "Constraints/OgreBulletDynamicsPoint2pointConstraint.h"
#include "Constraints/OgreBulletDynamicsConeTwistConstraint.h"
#include "BulletDynamics/ConstraintSolver/btConeTwistConstraint.h"


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
void Constraints_Demo::init(Ogre::Root *root, Ogre::RenderWindow *win, OgreBulletApplication *application)
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
    //mCamera->setFOVy(Degree(90));
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
    setBasicLight();
    
    // ------------------------
    // Add the Gui
    setPhysicGUI();
    // ------------------------
    // Start Bullet
    initWorld();

    // ------------------------
    // Add the ground
    //addGround();
    addStaticPlane(0.3, 0.8);

    OgreBulletDynamics::RigidBody *bodyA = addCube("corpsA",
                                                  Ogre::Vector3(13,  -0.25, -5),
                                                  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X),
                                                  Ogre::Vector3(1, 1, 1),
                                                  0.3, 0.8, 1.0);


    OgreBulletDynamics::RigidBody *bodyB = addCube("corpsB",
                                                  Ogre::Vector3(11,  -0.25, -5),
                                                  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X),
                                                  Ogre::Vector3(1, 1, 1),
                                                  0.3, 0.8, 1.0);

    /*
    OgreBulletDynamics::PointToPointConstraint *p2p = new OgreBulletDynamics::PointToPointConstraint(body,Ogre::Vector3(0,5,0));
    mWorld->addConstraint(p2p);
    */

    btTransform frameInA, frameInB;
    frameInA = btTransform::getIdentity();
    frameInA.getBasis().setEulerZYX(0, 0, 3.14/2.0);
    frameInA.setOrigin(btVector3(btScalar(0.), btScalar(-5.), btScalar(0.)));
    frameInB = btTransform::getIdentity();
    frameInB.getBasis().setEulerZYX(0,0,  3.14/2.0);
    frameInB.setOrigin(btVector3(btScalar(0.), btScalar(5.), btScalar(0.)));
    btTypedConstraint *ct = new btConeTwistConstraint(*bodyA->getBulletRigidBody(),*bodyB->getBulletRigidBody(),frameInA,frameInB);


    mWorld->getBulletDynamicsWorld()->addConstraint(ct);


    //OgreBulletDynamics::ConeTwistConstraint *ct = new OgreBulletDynamics::ConeTwistConstraint();
}
// -------------------------------------------------------------------------
void Constraints_Demo::keyPressed(BULLET_KEY_CODE key)
{
    OgreBulletListener::throwDynamicObject (key);
    OgreBulletListener::dropDynamicObject (key);

    return OgreBulletListener::keyPressed (key);
}

