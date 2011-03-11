/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#include "Terrain_Demo.h" 

#include "Shapes/OgreBulletCollisionsTerrainShape.h"
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

	static float	gRollInfluence = 
		//0.1f;
		1.0f;
	static float   gSuspensionRestLength = 0.6;
	static float   gMaxSuspensionTravelCm = 500.0;
	static float   gFrictionSlip = 10.5;

	static const Ogre::Vector3    CameraStart            = Ogre::Vector3(0, 25, 0);
	// -------------------------------------------------------------------------
	static const Ogre::Vector3   CarPosition             = Ogre::Vector3(15, 3,-15);

	static const float terrain_height = 45;
	static const Ogre::Vector3 terrain_Shift = Ogre::Vector3(750, terrain_height, 750);


#define CUBE_HALF_EXTENTS 1

// -------------------------------------------------------------------------
void Terrain_Demo::init(Ogre::Root *root, Ogre::RenderWindow *win, OgreBulletApplication *application)
{

	mCameraMove = 1;


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
    mSceneMgr = root->createSceneManager( "TerrainSceneManager", "BulletTerrain");

    mCamera = mSceneMgr->createCamera("Cam");
    //mCamera->setFOVy(Degree(90));
    mCamera->setNearClipDistance(0.1);
    mCamera->setFarClipDistance(1000);
    Viewport *vp = win->addViewport(mCamera);
    vp->setBackgroundColour(ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    mCamera->setPosition(CameraStart + terrain_Shift);
    mCamera->lookAt(CarPosition + terrain_Shift);


	// Create a terrain
	std::string terrain_cfg("terrain.cfg");
	mSceneMgr->setWorldGeometry(terrain_cfg);

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
    //addStaticPlane(0.3, 0.8);

	{
		Ogre::ConfigFile config;

		config.loadFromResourceSystem(terrain_cfg, ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME, "=", true);

        unsigned page_size = Ogre::StringConverter::parseUnsignedInt(config.getSetting( "PageSize" ));

        Ogre::Vector3 terrainScale(Ogre::StringConverter::parseReal( config.getSetting( "PageWorldX" ) ) / (page_size-1),
                                   Ogre::StringConverter::parseReal( config.getSetting( "MaxHeight" ) ),
                                   Ogre::StringConverter::parseReal( config.getSetting( "PageWorldZ" ) ) / (page_size-1));

        Ogre::String terrainfileName = config.getSetting( "Heightmap.image" );

        float *heights = new float [page_size*page_size];

        Ogre::Image terrainHeightMap;
        terrainHeightMap.load(terrainfileName, Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
        
        for(unsigned y = 0; y < page_size; ++y)
        {
            for(unsigned x = 0; x < page_size; ++x)
            {
                Ogre::ColourValue color = terrainHeightMap.getColourAt(x, y, 0);
                heights[x + y * page_size] = color.r;
            }
        }

		mTerrainShape = new HeightmapCollisionShape (
			page_size, 
			page_size, 
			terrainScale, 
			heights, 
			true);

		RigidBody *defaultTerrainBody = new RigidBody(
			"Terrain", 
			mWorld);

		const float      terrainBodyRestitution  = 0.1f;
		const float      terrainBodyFriction     = 0.8f;

        Ogre::Vector3 terrainShiftPos( (terrainScale.x * (page_size - 1) / 2), \
                                        0,
                                       (terrainScale.z * (page_size - 1) / 2));

        terrainShiftPos.y = terrainScale.y / 2 * terrainScale.y;

		Ogre::SceneNode* pTerrainNode = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
		defaultTerrainBody->setStaticShape (pTerrainNode, mTerrainShape, terrainBodyRestitution, terrainBodyFriction, terrainShiftPos);

		mBodies.push_back(defaultTerrainBody);
		mShapes.push_back(mTerrainShape);
	}




    // create obstacle in front of car
    addCube("obstacle", Ogre::Vector3(13,  -5.25, -5) + terrain_Shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(15,  -5.25, -5) + terrain_Shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(17,  -5.25, -5) + terrain_Shift ,  Quaternion(Radian(Degree(22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

    addCube("obstacle", Ogre::Vector3(13,  -5.25, -10) + terrain_Shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(15,  -5.25, -10) + terrain_Shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(17,  -5.25, -10) + terrain_Shift , Quaternion(Radian(Degree(-22.5)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

    // create obstacle a bit aside
    addCube("obstacle", Ogre::Vector3(-2,  0, -5) + terrain_Shift ,  Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(0,  0, -5) + terrain_Shift ,   Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(2,  0, -5) + terrain_Shift ,   Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

    addCube("obstacle", Ogre::Vector3(-2,  0, -10) + terrain_Shift , Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(0,  0, -10) + terrain_Shift ,  Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(2,  0, -10) + terrain_Shift ,  Quaternion(Radian(Degree(-45.0)), Ogre::Vector3::UNIT_X), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);

    // create obstacle just for fun
    addCube("obstacle", Ogre::Vector3(25, -10, -25) + terrain_Shift , Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(25, -10, -27) + terrain_Shift , Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);
    addCube("obstacle", Ogre::Vector3(25, -10, -29) + terrain_Shift , Quaternion(Radian(Degree(45.0)), Ogre::Vector3::UNIT_Z), Ogre::Vector3(1, 1, 1), 0.3, 0.8, 0);




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



		CompoundCollisionShape* compound = new CompoundCollisionShape();

		BoxCollisionShape* chassisShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));
        compound->addChildShape(chassisShape, chassisShift); 

        mCarChassis = new WheeledRigidBody("carChassis", mWorld);

        mCarChassis->setShape (node, 
			compound, 
			0.6, //restitution
			0.6, //friction
			800, //bodyMass
			CarPosition +  terrain_Shift , 
			Quaternion::IDENTITY);
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
void Terrain_Demo::keyPressed(BULLET_KEY_CODE key)
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
void Terrain_Demo::keyReleased(BULLET_KEY_CODE key)
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
bool Terrain_Demo::frameStarted(Real elapsedTime)
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