/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#include "Vehicle_Demo.h" 

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"

#if !(OGRE_VERSION <  ((1 << 16) | (3 << 8) | 0))
using namespace OIS;
#endif 

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;



///btRaycastVehicle is the interface for the constraint that implements the raycast vehicle
///notice that for higher-quality slow-moving vehicles, another approach might be better
///implementing explicit hinged-wheel constraints with cylinder collision, rather then raycasts


static float	gMaxEngineForce = 3000.f;

static float	gSteeringIncrement = 0.04f;
static float	gSteeringClamp = 0.8f;

static float	gWheelRadius = 0.5f;
static float	gWheelWidth = 0.4f;

static float	gWheelFriction = 1e30f;//1000;//1e30f;
static float	gSuspensionStiffness = 20.f;
static float	gSuspensionDamping = 2.3f;
static float	gSuspensionCompression = 4.4f;

static float	gRollInfluence = 0.1f;//1.0f;
static float   gSuspensionRestLength = 0.6;
static float   gMaxSuspensionTravelCm = 500.0;
static float   gFrictionSlip = 10.5;

static const Ogre::Vector3    CameraStart            = Ogre::Vector3(0, 25, 0);
// -------------------------------------------------------------------------
static const Ogre::Vector3   CarPosition             = Ogre::Vector3(15, 3,-15);

#define CUBE_HALF_EXTENTS 1

// -------------------------------------------------------------------------
void Vehicles_Demo::init(Ogre::Root *root, Ogre::RenderWindow *win, OgreBulletApplication *application)
{
    mHelpKeys.clear();
    mHelpKeys.push_back (BASIC_HELP_INFO0);
    mHelpKeys.push_back (BASIC_HELP_INFO1);
    mHelpKeys.push_back (BASIC_HELP_INFO2);
    mHelpKeys.push_back (BASIC_HELP_INFO3);
    mHelpKeys.push_back (BASIC_HELP_INFO4);
    mHelpKeys.push_back (BASIC_HELP_INFO5);
    mHelpKeys.push_back (BASIC_HELP_INFO6);
    mHelpKeys.push_back ("Use Arrow Key to move Car.");

// reset
    for (int i = 0; i < 4; i++)
    {
        mWheelsEngine[i] = 0;
        mWheelsSteerable[i] = 0;
    }
    mWheelsEngineCount = 2;
    mWheelsEngine[0] = 0;
    mWheelsEngine[1] = 1;
    mWheelsEngine[2] = 2;
    mWheelsEngine[3] = 3;

    mWheelsSteerableCount = 2;
    mWheelsSteerable[0] = 0;
    mWheelsSteerable[1] = 1;
    //mWheelsSteerable[2] = 2;
    //mWheelsSteerable[3] = 3;

    mWheelEngineStyle = 0;
    mWheelSteeringStyle = 0;

    mSteeringLeft = false;
    mSteeringRight = false;

    mEngineForce = 0;
    mSteering = 0;

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
    mCamera->lookAt(CarPosition);



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
    
    // 0.1, 0.8
    addStaticPlane(0.3, 0.8);









    // create obstacle in front of car
    addCube("obstacle", Ogre::Vector3(13,  -0.25, -5),  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(15,  -0.25, -5),  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(17,  -0.25, -5),  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

    addCube("obstacle", Ogre::Vector3(13,  -0.25, -10), Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(15,  -0.25, -10), Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(17,  -0.25, -10), Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

    // create obstacle a bit aside
    addCube("obstacle", Ogre::Vector3(-2,  0, -5),  Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(0,  0, -5),   Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(2,  0, -5),   Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

    addCube("obstacle", Ogre::Vector3(-2,  0, -10), Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(0,  0, -10),  Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(2,  0, -10),  Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

    // create obstacle just for fun
    addCube("obstacle", Ogre::Vector3(25, 0, -25), Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(25, 0, -27), Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(25, 0, -29), Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);




    /// create vehicle
	{
		const Ogre::Vector3 chassisShift(0, 1.0, 0);
		float connectionHeight = 0.7f;

        mChassis = mSceneMgr->createEntity(
                "chassis" + StringConverter::toString(mNumEntitiesInstanced++),
                "chassis.mesh");

        SceneNode *node = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();

        SceneNode *chassisnode = node->createChildSceneNode ();
        chassisnode->attachObject (mChassis);
        chassisnode->setPosition (chassisShift);


        mChassis->setQueryFlags (GEOMETRY_QUERY_MASK);
#if (OGRE_VERSION < ((1 << 16) | (5 << 8) | 0)) // only applicable before shoggoth (1.5.0)
        mChassis->setNormaliseNormals(true);
#endif
		mChassis->setCastShadows(true);



        BoxCollisionShape* chassisShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));
        CompoundCollisionShape* compound = new CompoundCollisionShape();
        compound->addChildShape(chassisShape, chassisShift); 

        mCarChassis = new WheeledRigidBody("carChassis", mWorld);

        mCarChassis->setShape (node, compound, 0.6, 0.6, 800, CarPosition, Quaternion::IDENTITY);
        mCarChassis->setDamping(0.2, 0.2);

        mCarChassis->disableDeactivation ();
        mTuning = new VehicleTuning(
            gSuspensionStiffness,
            gSuspensionCompression,
            gSuspensionDamping,
            gMaxSuspensionTravelCm,
            gFrictionSlip);

        mVehicleRayCaster = new VehicleRayCaster(mWorld);
        mVehicle = new RaycastVehicle(mCarChassis, mTuning, mVehicleRayCaster);

        {
            int rightIndex = 0;
            int upIndex = 1;
            int forwardIndex = 2;

            mVehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);

            Ogre::Vector3 wheelDirectionCS0(0,-1,0);
            Ogre::Vector3 wheelAxleCS(-1,0,0);

            for (size_t i = 0; i < 4; i++)
            {
                mWheels[i] = mSceneMgr->createEntity(
                    "wheel" + StringConverter::toString(mNumEntitiesInstanced++),
                    "wheel.mesh");

                mWheels[i]->setQueryFlags (GEOMETRY_QUERY_MASK);
#if (OGRE_VERSION < ((1 << 16) | (5 << 8) | 0)) // only applicable before shoggoth (1.5.0)
                mWheels[i]->setNormaliseNormals(true);
#endif
				mWheels[i]->setCastShadows(true);

                mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
                mWheelNodes[i]->attachObject (mWheels[i]);

            }

            {
                bool isFrontWheel = true;

                Ogre::Vector3 connectionPointCS0 (
                    CUBE_HALF_EXTENTS-(0.3*gWheelWidth),
                    connectionHeight,
                    2*CUBE_HALF_EXTENTS-gWheelRadius);


                mVehicle->addWheel(
                    mWheelNodes[0],
                    connectionPointCS0,
                    wheelDirectionCS0,
                    wheelAxleCS,
                    gSuspensionRestLength,
                    gWheelRadius,
                    isFrontWheel, gWheelFriction, gRollInfluence);

                connectionPointCS0 = Ogre::Vector3(
                    -CUBE_HALF_EXTENTS+(0.3*gWheelWidth),
                    connectionHeight,
                    2*CUBE_HALF_EXTENTS-gWheelRadius);


                mVehicle->addWheel(
                    mWheelNodes[1],
                    connectionPointCS0,
                    wheelDirectionCS0,
                    wheelAxleCS,
                    gSuspensionRestLength,
                    gWheelRadius,
                    isFrontWheel, gWheelFriction, gRollInfluence);


                connectionPointCS0 = Ogre::Vector3(
                    -CUBE_HALF_EXTENTS+(0.3*gWheelWidth),
                    connectionHeight,
                    -2*CUBE_HALF_EXTENTS+gWheelRadius);

                isFrontWheel = false;
                mVehicle->addWheel(
                    mWheelNodes[2],
                    connectionPointCS0,
                    wheelDirectionCS0,
                    wheelAxleCS,
                    gSuspensionRestLength,
                    gWheelRadius,
                    isFrontWheel, gWheelFriction, gRollInfluence);

                connectionPointCS0 = Ogre::Vector3(
                    CUBE_HALF_EXTENTS-(0.3*gWheelWidth),
                    connectionHeight,
                    -2*CUBE_HALF_EXTENTS+gWheelRadius);

                mVehicle->addWheel(
                    mWheelNodes[3],
                    connectionPointCS0,
                    wheelDirectionCS0,
                    wheelAxleCS,
                    gSuspensionRestLength,
                    gWheelRadius,
                    isFrontWheel, gWheelFriction, gRollInfluence);

                //mVehicle->setWheelsAttached();

            }

        }
    }

}
// -------------------------------------------------------------------------
void Vehicles_Demo::keyPressed(BULLET_KEY_CODE key)
{
    OgreBulletListener::throwDynamicObject (key);
    OgreBulletListener::dropDynamicObject (key);

    bool wheel_engine_style_change = false;
    bool wheel_steering_style_change = false;

    switch(key)
    {

    case KC_PGUP: 
        wheel_engine_style_change = true;
        mWheelEngineStyle = (mWheelEngineStyle + 1) % 3;
        break;
    case KC_PGDOWN: 
        wheel_engine_style_change = true;
        mWheelEngineStyle = (mWheelEngineStyle - 1) % 3;
        break;
    case KC_HOME: 
        wheel_steering_style_change = true;
        mWheelSteeringStyle = (mWheelSteeringStyle + 1) % 3;
        break;
    case KC_END: 
        wheel_steering_style_change = true;
        mWheelSteeringStyle = (mWheelSteeringStyle - 1) % 3;;
        break;

    case KC_LEFT: 
        mSteeringLeft = true;
        break;
    case KC_RIGHT: 
        mSteeringRight = true;
        break;
    case KC_DOWN: 
        mEngineForce = -gMaxEngineForce;
        break;
    case KC_UP: 
        mEngineForce = gMaxEngineForce;
        break;
    default:
        break;

    }

    if (wheel_engine_style_change)
    {
        for (int i = 0; i < 4; i++)
            mWheelsEngine[i] = 0;

        if (mWheelEngineStyle < 0)
            mWheelEngineStyle = 2;

        switch (mWheelEngineStyle)
        {
        case 0://front
            mWheelsSteerableCount = 2;
            mWheelsSteerable[0] = 0;
            mWheelsSteerable[1] = 1;  
            break;
        case 1://back
            mWheelsSteerableCount = 2;
            mWheelsSteerable[0] = 2;
            mWheelsSteerable[1] = 3;  
            break;
        case 2://4x4
            mWheelsSteerableCount = 4;
            mWheelsSteerable[0] = 0;
            mWheelsSteerable[1] = 1;  
            mWheelsSteerable[2] = 2;
            mWheelsSteerable[3] = 3; 
            break;
        default:
            assert(0);
            break;
        }
    }

    if (wheel_steering_style_change)
    {
        for (int i = 0; i < 4; i++)
            mWheelsSteerable[i] = 0;

        if (mWheelSteeringStyle < 0)
            mWheelSteeringStyle = 2;

        switch (mWheelSteeringStyle)
        {
        case 0://front
            mWheelsEngineCount = 2;
            mWheelsEngine[0] = 0;
            mWheelsEngine[1] = 1;  
            break;
        case 1://back
            mWheelsEngineCount = 2;
            mWheelsEngine[0] = 2;
            mWheelsEngine[1] = 3;  
            break;
        case 2://4x4
            mWheelsEngineCount = 4;
            mWheelsEngine[0] = 0;
            mWheelsEngine[1] = 1;  
            mWheelsEngine[2] = 2;
            mWheelsEngine[3] = 3; 
            break;
        default:
            assert(0);
            break;
        }
    }

    return OgreBulletListener::keyPressed (key);
}
// -------------------------------------------------------------------------
void Vehicles_Demo::keyReleased(BULLET_KEY_CODE key)
{
    switch(key)
    {

    case KC_LEFT: 
        mSteeringLeft = false;
        break;
    case KC_RIGHT: 
        mSteeringRight = false;
        break;
    case KC_DOWN: 
        mEngineForce = 0;
        break;
    case KC_UP: 
        mEngineForce = 0;
        break;
    default:
        break;

    }
    return OgreBulletListener::keyReleased (key);
}
// -------------------------------------------------------------------------
bool Vehicles_Demo::frameStarted(Real elapsedTime)
{

    // apply engine Force on relevant wheels
    for (int i = mWheelsEngine[0]; i < mWheelsEngineCount; i++)
    {
        mVehicle->applyEngineForce (mEngineForce, mWheelsEngine[i]);
    }

    if (mSteeringLeft)
    {
        mSteering += gSteeringIncrement;
        if (mSteering > gSteeringClamp)
            mSteering = gSteeringClamp;
    }
    else if (mSteeringRight)
    {
        mSteering -= gSteeringIncrement;
        if (mSteering < -gSteeringClamp)
            mSteering = -gSteeringClamp;
    }

    // apply Steering on relevant wheels
    for (int i = mWheelsSteerable[0]; i < mWheelsSteerableCount; i++)
    {
        if (i < 2)
            mVehicle->setSteeringValue (mSteering, mWheelsSteerable[i]);
        else
            mVehicle->setSteeringValue (-mSteering, mWheelsSteerable[i]);
    }

    return OgreBulletListener::frameStarted(elapsedTime);
}
// -------------------------------------------------------------------------