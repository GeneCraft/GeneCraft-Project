/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)
For the latest info, see http://www.ogre3d.org/phpBB2addons/viewforum.php?f=10

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



This source file is not LGPL, it's public source code that you can reuse.
-----------------------------------------------------------------------------*/
#include "OgreBulletApplication.h"
#include "OgreBulletListener.h"
#include "OgreBulletGuiListener.h"
#include "OgreBulletInputListener.h"

#include "OgreBulletCollisionsShape.h"

 
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Shapes/OgreBulletCollisionsConeShape.h"
#include "Shapes/OgreBulletCollisionsCylinderShape.h"
#include "Shapes/OgreBulletCollisionsTriangleShape.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"

#include "Shapes/OgreBulletCollisionsCompoundShape.h"

#include "Shapes/OgreBulletCollisionsMultiSphereShape.h"

#include "Shapes/OgreBulletCollisionsConvexHullShape.h"
#include "Shapes/OgreBulletCollisionsMinkowskiSumShape.h"

#include "Shapes/OgreBulletCollisionsTrimeshShape.h"

#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"

#include "OgreBulletCollisionsRay.h"

#include "Debug/OgreBulletCollisionsDebugLines.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"

#include "OgreBulletDynamicsConstraint.h"
#include "Constraints/OgreBulletDynamicsPoint2pointConstraint.h" 

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;
//using namespace OgreBulletLoader;

#if !(OGRE_VERSION <  ((1 << 16) | (3 << 8) | 0))
using namespace OIS;
#endif //OGRE_VERSION not Eihort

size_t OgreBulletListener::mNumEntitiesInstanced = 0;

// -------------------------------------------------------------------------
Ogre::ShadowTechnique convertToShadowTechnique(int i)
{
    switch(i)
    {
    case 0: return SHADOWTYPE_NONE;
    case 1: return SHADOWDETAILTYPE_ADDITIVE;
    case 2: return SHADOWDETAILTYPE_MODULATIVE;
    case 3: return SHADOWDETAILTYPE_INTEGRATED;
    case 4: return SHADOWDETAILTYPE_STENCIL;
    case 5: return SHADOWDETAILTYPE_TEXTURE;
    case 6: return SHADOWTYPE_STENCIL_MODULATIVE;
    case 7: return SHADOWTYPE_STENCIL_ADDITIVE;
    case 8: return SHADOWTYPE_TEXTURE_MODULATIVE;
    case 9: return SHADOWTYPE_TEXTURE_ADDITIVE;
    case 10: return SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED;
    case 11: return SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED;
    default: return SHADOWTYPE_NONE;
    }
}
// -------------------------------------------------------------------------
int convertShadowTechniqueToInt(Ogre::ShadowTechnique i)
{
	switch(i)
	{
	case  SHADOWTYPE_NONE: return 0;
	case  SHADOWDETAILTYPE_ADDITIVE: return 1;
	case  SHADOWDETAILTYPE_MODULATIVE: return 2;
	case  SHADOWDETAILTYPE_INTEGRATED: return 3;
	case  SHADOWDETAILTYPE_STENCIL: return 4;
	case  SHADOWDETAILTYPE_TEXTURE: return 5;
	case  SHADOWTYPE_STENCIL_MODULATIVE: return 6;
	case  SHADOWTYPE_STENCIL_ADDITIVE: return 7;
	case  SHADOWTYPE_TEXTURE_MODULATIVE: return 8;
	case  SHADOWTYPE_TEXTURE_ADDITIVE: return 9;
	case  SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED: return 10;
	case  SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED: return 11;
	default: return 0;
	}
}
// -------------------------------------------------------------------------
const Ogre::ColourValue g_minLightColour(0.2, 0.1, 0.0);
const Ogre::ColourValue g_maxLightColour(0.5, 0.3, 0.1);
// -------------------------------------------------------------------------

const float      gStaticBodyRestitution  = 0.1f;
const float      gStaticBodyFriction     = 0.9f;

const float      gDynamicBodyRestitution = 0.3f;
const float      gDynamicBodyFriction    = 0.6f;
const float      gDynamicBodyMass        = 3.0f;

const Ogre::Vector3    gCubeBodyBounds      = Ogre::Vector3 (1, 1, 1);
const Ogre::Vector3    gCylinderBodyBounds  = Ogre::Vector3 (0.5, 1, 0.5); 
const Ogre::Vector3    gConeBodyBounds      = Ogre::Vector3 (1, 1, 1);
const Real       gSphereBodyBounds    = 1.0f;
// -------------------------------------------------------------------------
OgreBulletListener::OgreBulletListener() :    
mCameraMove (0.1f),
mCameraTrans (Ogre::Vector3::ZERO),
mCamera(0),
mRoot(0),
mSceneMgr(0),
mWindow(0),
mWorld(0),
mStatsOn (true),
mPaused (true),
mShootSpeed (7.f),
mImpulseForce (10.f),
mDebugRayLine(0),
mRayQuery(0),
mInputListener(0),
mGuiListener(0),
mPickConstraint(0),
mCollisionClosestRayResultCallback(0)
{


}
// -------------------------------------------------------------------------
void OgreBulletListener::init(Ogre::Root *root, Ogre::RenderWindow *win, OgreBulletApplication *application)
{
    mRoot = root;
    mWindow = win;
    mApplication = application;
    mCameraTrans = Ogre::Vector3::ZERO;

    mGuiListener = new OgreBulletGuiListener(this, win);

    mInputListener = new OgreBulletInputListener(this, win);

    /******************* CREATESHADOWS ***************************/
#ifndef _DEBUG
    mCurrentShadowTechnique = convertShadowTechniqueToInt(SHADOWTYPE_TEXTURE_ADDITIVE);

	mSceneMgr->setShadowColour(ColourValue(0.5, 0.5, 0.5));

	Ogre::PixelFormat pxlFmt = Ogre::PF_L8;
	if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_TEXTURE_FLOAT))
	{
		const bool isOpenGL = (Ogre::Root::getSingleton().getRenderSystem()->getName().find("GL") != Ogre::String::npos);
		if (isOpenGL)// GL performs much better if you pick half-float format
			pxlFmt = Ogre::PF_FLOAT16_R;
		else
			pxlFmt = Ogre::PF_FLOAT32_R;// D3D is the opposite - if you ask for PF_FLOAT16_R you
		// get an integer format instead! You can ask for PF_FLOAT16_GR
		// but the precision doesn't work well

	}
	if (pxlFmt != Ogre::PF_L8)
	{
		String CUSTOM_CASTER_MATERIAL("Ogre/DepthShadowmap/Caster/Float");
		String CUSTOM_RECEIVER_MATERIAL("Ogre/DepthShadowmap/Receiver/Float");
		mSceneMgr->setShadowTextureSelfShadow(true);
		mSceneMgr->setShadowTextureCasterMaterial(CUSTOM_CASTER_MATERIAL);
		mSceneMgr->setShadowTextureReceiverMaterial(CUSTOM_RECEIVER_MATERIAL + "/PCF");
		//mSceneMgr->setShadowTextureReceiverMaterial(CUSTOM_RECEIVER_MATERIAL);
	}

	
	
	Ogre::LiSPSMShadowCameraSetup *mLiSPSMSetup = new Ogre::LiSPSMShadowCameraSetup();
	mLiSPSMSetup->setUseAggressiveFocusRegion(true);
	//mLiSPSMSetup->setUseSimpleOptimalAdjust(true);
	mLiSPSMSetup->setOptimalAdjustFactor(1.1f);
	mSceneMgr->setShadowCameraSetup(Ogre::ShadowCameraSetupPtr(mLiSPSMSetup));


	mSceneMgr->setShadowTechnique(convertToShadowTechnique(mCurrentShadowTechnique));
	if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_HWRENDER_TO_TEXTURE))
	{
		// In D3D, use a 1024x1024 shadow texture
		mSceneMgr->setShadowTextureSettings(2048, 2, pxlFmt);
	}
	else
	{
		// Use 512x512 texture in GL since we can't go higher than the window res
		mSceneMgr->setShadowTextureSettings(512, 2, pxlFmt);
	}


#endif // _DEBUG

    /******************* CREATE Queries ***************************/
    mRayQuery = mSceneMgr->createRayQuery(Ray());
    mRayQuery->setQueryMask (GEOMETRY_QUERY_MASK);
    mRayQuery->setQueryTypeMask(SceneManager::ENTITY_TYPE_MASK);
    MovableObject::setDefaultQueryFlags (ANY_QUERY_MASK);

    //
    mQuit = false;
    mPaused = false;
    mActivationBool = false;

    mPickConstraint = 0;

    mWireFrame = false;
    mDrawAabb = false;
    mDrawFeaturesText = false;
    mDrawContactPoints = false;
    mNoDeactivation = false;
    mNoHelpText = false;
    mDrawText = false;
    mProfileTimings = false;
    mEnableSatComparison = false;
    mDisableBulletLCP = false;
    mEnableCCD = false;

}
// -------------------------------------------------------------------------
void OgreBulletListener::setBasicLight()
{
    // Set ambient light
    mSceneMgr->setAmbientLight(ColourValue(0.4, 0.4, 0.4));

	// Fixed light, dim
// 	mSunLight = mSceneMgr->createLight("Sun");
// 	mSunLight->setPosition(0.0, 30.5, 0.0);
// 	mSunLight->setCastShadows(false);
// 	mSunLight->setType(Light::LT_POINT);
// 	mSunLight->setDiffuseColour(g_minLightColour);
// 	mSunLight->setSpecularColour(0.2, 0.2, 0.2);
// 	mSunLight->setAttenuation(8000, 1, 0.0005, 0);

	// Point light, movable, reddish
	mLight = mSceneMgr->createLight("Spot");
	mLight->setType(Light::LT_SPOTLIGHT);
	mLight->setPosition(100.0, 80.5,-10.0);
	mLight->setSpotlightRange(Degree(30), Degree(50));
	Ogre::Vector3 dir;
	dir = -mLight->getPosition();
	dir.normalise();
	mLight->setDirection(dir);
	mLight->setDiffuseColour(0.70, 0.70, 0.72);
	mLight->setSpecularColour(0.1, 0.1, 0.3);


	mLight2 = mSceneMgr->createLight("Spot2");
	mLight2->setType(Light::LT_SPOTLIGHT);
	mLight2->setPosition(-100.0, 80.5, 10.0);
	mLight2->setSpotlightRange(Degree(30), Degree(50));
	dir = -mLight2->getPosition();
	dir.normalise();
	mLight2->setDirection(dir);
	mLight2->setDiffuseColour(0.72, 0.70, 0.70);
	mLight2->setSpecularColour(0.3, 0.1, 0.1);

}
// -------------------------------------------------------------------------
void OgreBulletListener::setPhysicGUI()
{
    BetaGUI::GUI *gui = mGuiListener->getGui ();

    BetaGUI::Window *menuWindow = gui->addMenuWindow(
        Vector2(mWindow->getWidth(), 24));
    menuWindow->hide ();


    BetaGUI::Window *aWindow;


    aWindow = menuWindow->addMenuWindowTab("Scene Choice");
    {
        std::vector <OgreBulletListener *> *sceneList = mApplication->getScenesList();
        std::vector <OgreBulletListener *>::iterator itScenes = sceneList->begin();
        for (;itScenes < sceneList->end(); ++itScenes)
        {
            if ((*itScenes) == this)
                aWindow->addBoolButton((*itScenes)->getBoolActivator(), "reset " + (*itScenes)->getName(), BetaGUI::WPT_VERTICAL);
            else
                aWindow->addBoolButton((*itScenes)->getBoolActivator(), (*itScenes)->getName(), BetaGUI::WPT_VERTICAL);
        }
    }
    aWindow->hide ();


    aWindow = menuWindow->addMenuWindowTab("Time", false, BetaGUI::WPT_NONE);
    aWindow->addBoolButton(&mPaused, "Play/Pause", BetaGUI::WPT_HORIZONTAL);
    aWindow->addBoolButton(&mDoOnestep, "Single Step", BetaGUI::WPT_HORIZONTAL);
    aWindow->hide ();

    // appears and slide in
    const Vector2 screenRightTop (mWindow->getWidth () - aWindow->getSize ().x, 0);
    const Vector2 screenRightOffTop (mWindow->getWidth () - aWindow->getSize ().x, - aWindow->getSize ().y);
    gui->addEffect(new BetaGUI::MoveEffect(aWindow, 2, screenRightOffTop, screenRightTop, 0));
    gui->addEffect(new BetaGUI::AlphaEffect(aWindow, 2, 0, 1, 0));

    aWindow = menuWindow->addMenuWindowTab("Interaction");
    aWindow->addRealButton(&mShootSpeed,
        Vector4(0.1, 5.0, 0.0, 100.0),
        "Shoot Speed:", BetaGUI::WPT_VERTICAL);
    aWindow->addRealButton(&mImpulseForce,
        Vector4(0.1, 5.0, 0.0, 100.0),
        "Impulse Force:", BetaGUI::WPT_VERTICAL);
    aWindow->hide ();

    aWindow = menuWindow->addMenuWindowTab("Debug");
    aWindow->addBoolButton(&mWireFrame, "Draw Wireframe", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mDrawAabb, "Draw Aabb", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mDrawFeaturesText, "Draw Features Text", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mDrawContactPoints, "Draw Contact Points", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mNoDeactivation, "No Deactivation", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mNoHelpText, "No Help Text", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mDrawText, "Draw Text", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mProfileTimings, "Profile Timings", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mEnableSatComparison, "Enable Sat Comparison", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mDisableBulletLCP, "Disable Bullet LCP", BetaGUI::WPT_VERTICAL);
    aWindow->addBoolButton(&mEnableCCD, "Enable CCD", BetaGUI::WPT_VERTICAL);
    aWindow->hide ();

    aWindow = menuWindow ->addMenuWindowTab("FPS", false, BetaGUI::WPT_NONE);
    mFpsStaticText = aWindow->addStaticText("FPS Count", BetaGUI::WPT_VERTICAL);
    aWindow->hide ();
    // appears and slide in
    const Vector2 screenRightBottom (mWindow->getWidth () - 360, mWindow->getHeight () - 24);
    const Vector2 screenRightOffBottom (mWindow->getWidth () - 360, mWindow->getHeight ());
    gui->addEffect(new BetaGUI::MoveEffect(aWindow, 2, screenRightOffBottom, screenRightBottom, 0));
    gui->addEffect(new BetaGUI::AlphaEffect(aWindow, 2, 0, 1, 0));


    aWindow = menuWindow->addMenuWindowTab("Help");
    aWindow->addStaticText(mName + " Help Informations", BetaGUI::WPT_VERTICAL);

    std::vector <String>::iterator keyIterator = mHelpKeys.begin();
    for (;keyIterator < mHelpKeys.end(); ++keyIterator)
    {
        aWindow->addStaticText(*keyIterator, BetaGUI::WPT_VERTICAL); 
    }

    // appears and slide
    const Vector2 halfWindowSize (aWindow->getSize ().x / 2, aWindow->getSize ().y / 2);
    const Vector2 screenCentered ((mWindow->getWidth () / 2) - halfWindowSize.x,
        (mWindow->getHeight () / 2) - halfWindowSize.y);
    gui->addEffect(new BetaGUI::MoveEffect(aWindow, 2, -halfWindowSize, screenCentered, 0));
    gui->addEffect(new BetaGUI::AlphaEffect(aWindow, 2, 0, 1, 0));
    // disappears
    gui->addEffect(new BetaGUI::AlphaEffect(aWindow, 2, 1, 0, 3));

    menuWindow->addBoolButton(&mQuit, "Quit", BetaGUI::WPT_HORIZONTAL);

    // appears and slide in
    const Vector2 screenLeftTop (- menuWindow->getSize ().x, 0);
    const Vector2 screenLeftOffTop (0, 0);
    gui->addEffect(new BetaGUI::MoveEffect(menuWindow, 2, screenLeftTop, screenLeftOffTop, 0));
    gui->addEffect(new BetaGUI::AlphaEffect(menuWindow, 2, 0, 1, 0));
}
// -------------------------------------------------------------------------
void OgreBulletListener::getDebugLines()
{
    if (mDebugRayLine == 0)
    {
        mDebugRayLine = new DebugLines();
        mSceneMgr->getRootSceneNode ()->createChildSceneNode ()->attachObject (mDebugRayLine);
    }
}
// -------------------------------------------------------------------------
void OgreBulletListener::shutdown ()
{
    delete mInputListener;
    delete mGuiListener;

    // OgreBullet physic delete 
    std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
    while (mBodies.end() != itBody)
    {   
        delete *itBody; 
        ++itBody;
    }

    delete mWorld->getDebugDrawer();
    mWorld->setDebugDrawer(0);
    delete mWorld;

    // Ogre delete 
    mSceneMgr->destroyQuery (mRayQuery);
    std::deque<Ogre::Entity *>::iterator itEntity = mEntities.begin();
    while (mEntities.end() != itEntity)
    {
        SceneNode *node = static_cast<SceneNode*>((*itEntity)->getParentNode());
        node->detachObject(*itEntity);
        mSceneMgr->destroyEntity(*itEntity);
        assert (node->getParent());
        static_cast <SceneNode *> (node->getParent())->removeAndDestroyChild(node->getName());

        ++itEntity;
    }
    mEntities.clear();
    mSceneMgr->destroyCamera(mCamera->getName ());
    mWindow->removeViewport(0);
    mRoot->destroySceneManager (mSceneMgr);
    delete mDebugRayLine;

    mInputListener = 0;
    mGuiListener = 0;
    mRayQuery = 0;
    mWorld = 0;
    mCamera = 0;
    mSceneMgr = 0;
    mDebugRayLine = 0;

    mBodies.clear();
    mEntities.clear();
    mShapes.clear();

}

// -------------------------------------------------------------------------
void OgreBulletListener::button1Pressed()
{
    // pick a body and try to drag it.
    Ogre::Vector3 pickPos;
    Ogre::Ray rayTo;
    OgreBulletDynamics::RigidBody * body = 
        getBodyUnderCursorUsingBullet(pickPos, rayTo);
        //getBodyUnderCursorUsingOgre(pickPos, rayTo);
    if (body)
    {  
        //other exclusions?
        if (!(body->isStaticObject() 
            //|| body->isKinematicObject()
            ))
        {
            mPickedBody = body;
            mPickedBody->disableDeactivation();		
            const Ogre::Vector3 localPivot (body->getCenterOfMassPivot(pickPos));
            OgreBulletDynamics::PointToPointConstraint *p2p  = 
                new OgreBulletDynamics::PointToPointConstraint(body, localPivot);

            mWorld->addConstraint(p2p);					    

            //save mouse position for dragging
            mOldPickingPos = pickPos;
            const Ogre::Vector3 eyePos(mCamera->getDerivedPosition());
            mOldPickingDist  = (pickPos - eyePos).length();

            //very weak constraint for picking
            p2p->setTau (0.1f);
            mPickConstraint = p2p;


        }
        getDebugLines();
        mDebugRayLine->addLine (rayTo.getOrigin(), pickPos);
        mDebugRayLine->draw();
    }

    if (mGuiListener->getGui()->injectMouse(mInputListener->getAbsMouseX ()*mWindow->getWidth(), 
        mInputListener->getAbsMouseY ()*mWindow->getHeight(), true))
    {
        mGuiListener->hideMouse();
    }
    else
    {
        mGuiListener->showMouse ();
    }
}
// -------------------------------------------------------------------------
void OgreBulletListener::button0Pressed()
{

    // small unique impulse under cursor.
    Ogre::Vector3 pickPos;
    Ogre::Ray rayTo;
    OgreBulletDynamics::RigidBody * body = 
        getBodyUnderCursorUsingBullet(pickPos, rayTo);
        //getBodyUnderCursorUsingOgre(pickPos, rayTo);
    if (body)
    {  
        if (!(body->isStaticObject() 
            || body->isKinematicObject()
            ))
        {

            body->enableActiveState ();

            const Ogre::Vector3 relPos (pickPos - body->getCenterOfMassPosition());
            const Ogre::Vector3 impulse (rayTo.getDirection ());

            body->applyImpulse (impulse * mImpulseForce, relPos);		

        }

        getDebugLines();
        mDebugRayLine->addLine (rayTo.getOrigin(), pickPos);
        mDebugRayLine->draw();	
    }  
}
// -------------------------------------------------------------------------
void OgreBulletListener::button2Pressed()
{ 
    mGuiListener->hideMouse ();
}
// -------------------------------------------------------------------------
void OgreBulletListener::button0Released()
{
    if (mPickConstraint)
    {
        // was dragging, but button released
        // Remove constraint
        mWorld->removeConstraint(mPickConstraint);
        delete mPickConstraint;

        mPickConstraint = 0;
        mPickedBody->forceActivationState();
        mPickedBody->setDeactivationTime( 0.f );
        mPickedBody = 0;	

        getDebugLines();
        mDebugRayLine->addLine (Ogre::Vector3::ZERO, Ogre::Vector3::ZERO);	
        mDebugRayLine->draw();  
        mGuiListener->showMouse(); 
    }
}
// -------------------------------------------------------------------------
void OgreBulletListener::button1Released()
{
}
// -------------------------------------------------------------------------
void OgreBulletListener::button2Released()
{
    mGuiListener->showMouse ();
}
// -------------------------------------------------------------------------
void OgreBulletListener::mouseMoved()
{
    mGuiListener->setMousePosition(mInputListener->getAbsMouseX (), mInputListener->getAbsMouseY ());
    if (mPickConstraint)
    {
        // dragging
        //add a point to point constraint for picking	
        Ogre::Ray rayTo = mCamera->getCameraToViewportRay (mInputListener->getAbsMouseX(), mInputListener->getAbsMouseY());
        //move the constraint pivot
        OgreBulletDynamics::PointToPointConstraint * p2p = static_cast <OgreBulletDynamics::PointToPointConstraint *>(mPickConstraint);
        //keep it at the same picking distance

        const Ogre::Vector3 eyePos(mCamera->getDerivedPosition());

        //Ogre::Vector3 dir = rayTo.getDirection () - eyePos;
        //dir.normalise();
        //dir *= mOldPickingDist;
        Ogre::Vector3 dir = rayTo.getDirection () * mOldPickingDist;
        dir.normalise();

        const Ogre::Vector3 newPos (eyePos + dir);
        p2p->setPivotB (newPos);    

        setDebugText ("Dragging");

        getDebugLines();
        mDebugRayLine->addLine (mPickedBody->getWorldPosition (), newPos);
        mDebugRayLine->draw();
        mGuiListener->showMouse();
    }

    if (mGuiListener->getGui()->injectMouse(mInputListener->getAbsMouseX ()*mWindow->getWidth(), 
        mInputListener->getAbsMouseY ()*mWindow->getHeight(), mInputListener->getButton0Pressed()))
    {
        mGuiListener->hideMouse();
    }
    else 
    {
        mGuiListener->showMouse();
    }


    if (mInputListener->getButton2Pressed())
    {
        mCameraRotX = Degree(-mInputListener->getRelMouseX () * 0.13);
        mCameraRotY = Degree(-mInputListener->getRelMouseY () * 0.13);
    }

}
// -------------------------------------------------------------------------
void OgreBulletListener::keyPressed(BULLET_KEY_CODE key)
{
    static int count = 0;
    // Scene Debug Options

    switch(key)
    {
        // Application Utils
    case KC_ESCAPE:
        mQuit = true;
        break;

    case KC_SYSRQ:
        mWindow->writeContentsToFile("OgreBulletScreenShot"+StringConverter::toString(count++)+".png");
        break;

        // Scene Debug Options

    case KC_T:
        mWireFrame = true;
        break;
    case KC_1:
        mDrawAabb = true;
        break;
    case KC_2:
        mDrawFeaturesText = true;
        break;
    case KC_3:
        mDrawContactPoints = true;
        break;
    case KC_4:
        mNoDeactivation = true;
        break;
    case KC_5:
        mNoHelpText = true;
        break;
    case KC_6:
        mDrawText = true;
        break;
    case KC_7:
        mProfileTimings = true;
        break;
    case KC_8:
        mEnableSatComparison = true;
        break;
    case KC_9:
        mDisableBulletLCP = true;
        break;
    case KC_0:
        mEnableCCD = true;
        break;

        // pause
    case KC_P:
        mPaused = !mPaused;
        break;
        // single step
    case KC_M:
        mDoOnestep = true;
        break;
        // faster Shoots
    case KC_ADD:
        mShootSpeed += 5.0f;
        break;
        // Slower Shoots
    case KC_MINUS:
        mShootSpeed -= 5.0f;
        break;

        //Camera
    case KC_Z:
    case KC_W:
        mCameraTrans.z -= mCameraMove;
        break;

    case KC_S:
        mCameraTrans.z += mCameraMove;
        break;

    case KC_Q:
    case KC_A:
        mCameraTrans.x -= mCameraMove;
        break;

    case KC_D:
        mCameraTrans.x += mCameraMove;
        break;

    default:
        break;
    }
}
// -------------------------------------------------------------------------
void OgreBulletListener::keyReleased(BULLET_KEY_CODE key)
{
    switch(key)
    {
        //Camera
    case KC_Z:
    case KC_W:
        mCameraTrans.z += mCameraMove;
        break;
    case KC_S:
        mCameraTrans.z -= mCameraMove;
        break;
    case KC_Q:
    case KC_A:
        mCameraTrans.x += mCameraMove;
        break;
    case KC_D:
        mCameraTrans.x -= mCameraMove;
        break;

    default:
        break;
    }
}
// -------------------------------------------------------------------------
OgreBulletDynamics::RigidBody* OgreBulletListener::getBodyUnderCursorUsingBullet(Ogre::Vector3 &intersectionPoint, Ray &rayTo)
{
    rayTo = mCamera->getCameraToViewportRay (mInputListener->getAbsMouseX(), mInputListener->getAbsMouseY());

	delete mCollisionClosestRayResultCallback;
	mCollisionClosestRayResultCallback = new CollisionClosestRayResultCallback(rayTo, mWorld, mCamera->getFarClipDistance());

    mWorld->launchRay (*mCollisionClosestRayResultCallback);
    if (mCollisionClosestRayResultCallback->doesCollide ())
    {
        OgreBulletDynamics::RigidBody * body = static_cast <OgreBulletDynamics::RigidBody *> 
            (mCollisionClosestRayResultCallback->getCollidedObject());
		
		intersectionPoint = mCollisionClosestRayResultCallback->getCollisionPoint ();
        setDebugText("Hit :" + body->getName());
        return body;
    }
    return 0;
}
// -------------------------------------------------------------------------
OgreBulletDynamics::RigidBody* OgreBulletListener::getBodyUnderCursorUsingOgre(Ogre::Vector3 &intersectionPoint, Ray &rayTo)
{
    rayTo = mCamera->getCameraToViewportRay (mInputListener->getAbsMouseX(), mInputListener->getAbsMouseY());

    mRayQuery->setRay (rayTo);
    const RaySceneQueryResult& result = mRayQuery->execute();
    if (!result.empty())
    {
        RaySceneQueryResult::const_iterator i = result.begin();

        mRayQuery->setSortByDistance (true, 1);//only one hit
        while((i != result.end()))
        {
            SceneNode *node = i->movable->getParentSceneNode() ;
#if (OGRE_VERSION >=  ((1 << 16) | (5 << 8) | 0)) // must have at least shoggoth (1.5.0)
			intersectionPoint = node->_getDerivedPosition ();
#else
			intersectionPoint = node->getWorldPosition ();
#endif
            const unsigned short num = node->numAttachedObjects();
            MovableObject* movable;
            for (unsigned short cur = 0;cur < num; cur++)
            {
                movable = node->getAttachedObject(cur);
                if (movable->getMovableType() == OgreBulletCollisions::Object::mMovableType) 
                {
                    OgreBulletCollisions::Object *object = static_cast <OgreBulletCollisions::Object *>(movable);
                    OgreBulletDynamics::RigidBody *body = static_cast <OgreBulletDynamics::RigidBody *>(object);
                    setDebugText ("Hit :" + body->getName());

                    return body;
                }
            }
            ++i;
        }	
    }// if results.	 
    return 0;
}
// -------------------------------------------------------------------------
bool OgreBulletListener::frameStarted(Real elapsedTime)
{
    if (mQuit)
        return false;

    if (mInputListener->getButton2Pressed())
    {
        mCamera->yaw(mCameraRotX);
        mCamera->pitch(mCameraRotY);

        mCameraRotX = 0;
        mCameraRotY = 0;
    }

    mCamera->moveRelative(mCameraTrans);

    // update physics
    for(int i =0; i < 150000; i++) {
        if (!mPaused || mDoOnestep)
            mWorld->stepSimulation(elapsedTime);
    }
    mDoOnestep = false;

    return true;
}
// -------------------------------------------------------------------------
bool OgreBulletListener::frameEnded(Real elapsedTime)
{
    if (mQuit)
        return false;

    DebugDrawer *debugDrawer = mWorld->getDebugDrawer ();


    // Scene Debug Options
    if (mWireFrame)
    {
        const bool wasWireframeShapes = debugDrawer->doesDrawWireframe();
        debugDrawer->setDrawWireframe(!wasWireframeShapes);
        mWorld->setShowDebugShapes(!wasWireframeShapes);
        mWireFrame = false;
    }
    if (mDrawAabb) 
    {
        debugDrawer->setDrawAabb(!debugDrawer->doesDrawAabb());
        mDrawAabb = false;
    }
    if ( mDrawFeaturesText)
    {
        debugDrawer->setDrawFeaturesText(!debugDrawer->doesDrawFeaturesText());
        mDrawFeaturesText = false;
    }
    if ( mDrawContactPoints)
    {
        debugDrawer->setDrawContactPoints(!debugDrawer->doesDrawContactPoints());
		mWorld->setShowDebugContactPoints(debugDrawer->doesDrawContactPoints());
        mDrawContactPoints = false;
    }
    if ( mNoDeactivation)
    {
        debugDrawer->setNoDeactivation(!debugDrawer->doesNoDeactivation());
        mNoDeactivation = false;
    }
    if ( mNoHelpText)
    {
        debugDrawer->setNoHelpText(!debugDrawer->doesNoHelpText());
        mNoHelpText = false;
    }
    if ( mDrawText)
    {
        debugDrawer->setDrawText(!debugDrawer->doesDrawText());
        mDrawText = false;
    }
    if ( mProfileTimings)
    {
        debugDrawer->setProfileTimings(!debugDrawer->doesProfileTimings());
        mProfileTimings = false;
    }
    if ( mEnableSatComparison)
    {
        debugDrawer->setEnableSatComparison(!debugDrawer->doesEnableSatComparison());
        mEnableSatComparison = false;
    }
    if ( mDisableBulletLCP)
    {
        debugDrawer->setDisableBulletLCP(!debugDrawer->doesDisableBulletLCP());
        mDisableBulletLCP = false;
    }
    if ( mEnableCCD)
    {
        debugDrawer->setEnableCCD(!debugDrawer->doesEnableCCD());
        mEnableCCD = false;
    }

    mGuiListener->getGui ()->update (elapsedTime);
    updateStats();
    return true;
}
// ------------------------------------------------------------------------- 
bool OgreBulletListener::checkIfEnoughPlaceToAddObject(float maxDist)
{
    Ogre::Vector3 pickPos;
    Ogre::Ray rayTo;
    OgreBulletDynamics::RigidBody * body = 
        getBodyUnderCursorUsingBullet(pickPos, rayTo);
        //getBodyUnderCursorUsingOgre(pickPos, rayTo);
    if (body)
    {          
        if ((pickPos - mCamera->getDerivedPosition ()).length () < maxDist)
            return false;
    }
    return true;        
}
// -------------------------------------------------------------------------
void OgreBulletListener::throwDynamicObject(BULLET_KEY_CODE key)
{
    const float trowDist = 2.0f;
    switch(key)
    {
    case KC_B: 
        if ( checkIfEnoughPlaceToAddObject(trowDist))
        {
            const Ogre::Vector3 vec (mCamera->getDerivedPosition());
            OgreBulletDynamics::RigidBody *body = addCube("cube", vec, Quaternion(0,0,0,1), 
                gCubeBodyBounds, gDynamicBodyRestitution, gDynamicBodyFriction, gDynamicBodyMass);

            body->setLinearVelocity(
                mCamera->getDerivedDirection().normalisedCopy() * mShootSpeed
				);
		}
        break;
    case KC_N: 
        if ( checkIfEnoughPlaceToAddObject(trowDist))
        {
            const Ogre::Vector3 vec (mCamera->getDerivedPosition());
            OgreBulletDynamics::RigidBody *body = addSphere("sphere", vec, Quaternion(0,0,0,1), 
                gSphereBodyBounds, 
                gDynamicBodyRestitution, gDynamicBodyFriction, gDynamicBodyMass);

            body->setLinearVelocity(
                mCamera->getDerivedDirection().normalisedCopy() * mShootSpeed
                );
        }
        break;
    case KC_H: 
        if ( checkIfEnoughPlaceToAddObject(trowDist))
        {
            const Ogre::Vector3 vec (mCamera->getDerivedPosition());
            OgreBulletDynamics::RigidBody *body = addCylinder("cylinder", vec, Quaternion(0,0,0,1), 
                gCylinderBodyBounds, 
                gDynamicBodyRestitution, gDynamicBodyFriction, gDynamicBodyMass);

            body->setLinearVelocity(
                mCamera->getDerivedDirection().normalisedCopy() * mShootSpeed
                );
        }
        break;
    case KC_G : 
        if ( checkIfEnoughPlaceToAddObject(trowDist))
        {
            const Ogre::Vector3 vec (mCamera->getDerivedPosition());
            OgreBulletDynamics::RigidBody *body = addCone("cone", vec, Quaternion(0,0,0,1), 
                gConeBodyBounds, 
                gDynamicBodyRestitution, gDynamicBodyFriction, gDynamicBodyMass);

            body->setLinearVelocity(
                mCamera->getDerivedDirection().normalisedCopy() * mShootSpeed
                );
        }
        break;
    }
}
// -------------------------------------------------------------------------
void OgreBulletListener::dropDynamicObject(BULLET_KEY_CODE key)
{
    const float dropDist = 10.0f;
    switch(key)
    {
    case KC_J: 
        if ( checkIfEnoughPlaceToAddObject(dropDist))
        {
            const Ogre::Vector3 vec (mCamera->getDerivedPosition());
            OgreBulletDynamics::RigidBody *body = addCube("cube", 
                vec + mCamera->getDerivedDirection().normalisedCopy() * 10, 
                Quaternion(0,0,0,1), 
                gCubeBodyBounds, gDynamicBodyRestitution, gDynamicBodyFriction, gDynamicBodyMass);

        }
        break;
    case KC_K: 
        if ( checkIfEnoughPlaceToAddObject(dropDist))
        {
            const Ogre::Vector3 vec (mCamera->getDerivedPosition());
            OgreBulletDynamics::RigidBody *body = addSphere("sphere", 
                vec + mCamera->getDerivedDirection().normalisedCopy() * 10, 
                Quaternion(0,0,0,1), 
                gSphereBodyBounds, 
                gDynamicBodyRestitution, gDynamicBodyFriction, gDynamicBodyMass);

        }
        break;
    case KC_U : 
        if ( checkIfEnoughPlaceToAddObject(dropDist))
        {
            const Ogre::Vector3 vec (mCamera->getDerivedPosition());
            OgreBulletDynamics::RigidBody *body = addCylinder("Cylinder", vec, Quaternion(0,0,0,1), 
                gCylinderBodyBounds, 
                gDynamicBodyRestitution, gDynamicBodyFriction, gDynamicBodyMass);

        }
        break;
    case KC_I: 
        if ( checkIfEnoughPlaceToAddObject(dropDist))
        {
            const Ogre::Vector3 vec (mCamera->getDerivedPosition());
            OgreBulletDynamics::RigidBody *body = addCone("Cone", 
                vec + mCamera->getDerivedDirection().normalisedCopy() * 10, 
                Quaternion(0,0,0,1), 
                gConeBodyBounds, 
                gDynamicBodyRestitution, gDynamicBodyFriction, gDynamicBodyMass);
        }
        break;
    }
}
// -------------------------------------------------------------------------
void OgreBulletListener::initWorld(const Ogre::Vector3 &gravityVector, 
                                   const Ogre::AxisAlignedBox &bounds)
{
    // Start Bullet
    mWorld = new DynamicsWorld (mSceneMgr, bounds, gravityVector, true, true, 10000);

    // add Debug info display tool
    DebugDrawer *debugDrawer = new DebugDrawer();

    mWorld->setDebugDrawer(debugDrawer);

    SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
    node->attachObject (static_cast <SimpleRenderable *> (debugDrawer));


}
// -------------------------------------------------------------------------
void OgreBulletListener::addGround()
{
    addStaticPlane(
        gStaticBodyRestitution, 
        gStaticBodyFriction);
}
// -------------------------------------------------------------------------
RigidBody *OgreBulletListener::addCube(const Ogre::String instanceName,
                                       const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Vector3 &size,
                                       const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, 
                                       const Ogre::Real bodyMass)
{
    Entity *entity = mSceneMgr->createEntity(
        instanceName + StringConverter::toString(mNumEntitiesInstanced),
        "Bulletbox.mesh");
    // "Crate.mesh");
    // "Crate1.mesh");
    // "Crate2.mesh");


    entity->setQueryFlags (GEOMETRY_QUERY_MASK);
#if (OGRE_VERSION < ((1 << 16) | (5 << 8) | 0)) // only applicable before shoggoth (1.5.0)
    entity->setNormaliseNormals(true);
#endif
	entity->setCastShadows(true);

    entity->setMaterialName("Bullet/box");

    BoxCollisionShape *sceneCubeShape = new BoxCollisionShape(size);

    RigidBody *defaultBody = new RigidBody(
        "defaultCubeRigid" + StringConverter::toString(mNumEntitiesInstanced), 
        mWorld);

    SceneNode *node = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
    node->attachObject (entity);

    defaultBody->setShape (node,  sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);

    mEntities.push_back(entity);
    mShapes.push_back(sceneCubeShape);
    mBodies.push_back(defaultBody);
    mNumEntitiesInstanced++;

    return defaultBody;
}
// -------------------------------------------------------------------------
RigidBody *OgreBulletListener::addSphere(const Ogre::String instanceName,
                                         const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Real radius,
                                         const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, 
                                         const Ogre::Real bodyMass)
{
    Entity *entity = mSceneMgr->createEntity(
        instanceName + StringConverter::toString(mNumEntitiesInstanced),
        "ellipsoid.mesh");

    entity->setQueryFlags (GEOMETRY_QUERY_MASK);
#if (OGRE_VERSION < ((1 << 16) | (5 << 8) | 0)) // only applicable before shoggoth (1.5.0)
    entity->setNormaliseNormals(true);
#endif
	entity->setCastShadows(true);

    entity->setMaterialName("Bullet/box");

    SphereCollisionShape *sceneCubeShape = new SphereCollisionShape(radius);

    RigidBody *defaultBody = new RigidBody(
        "defaultSphereRigid" + StringConverter::toString(mNumEntitiesInstanced),
        mWorld);

    SceneNode *node = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
    node->attachObject (entity);

    defaultBody->setShape (node,  sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);

    mEntities.push_back(entity);
    mShapes.push_back(sceneCubeShape);
    mBodies.push_back(defaultBody);
    mNumEntitiesInstanced++;

    return defaultBody;
}

// -------------------------------------------------------------------------
RigidBody *OgreBulletListener::addCylinder(const Ogre::String instanceName,
                                           const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Vector3 &size,
                                           const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, 
                                           const Ogre::Real bodyMass)
{
    Entity *entity = mSceneMgr->createEntity(
        instanceName + StringConverter::toString(mNumEntitiesInstanced),
        "cylinder.mesh");
    //   "capsule.mesh");
    // "Barrel.mesh");
    // "Barrel1.mesh");
    // "Barrel2.mesh");

    entity->setQueryFlags (GEOMETRY_QUERY_MASK);
#if (OGRE_VERSION < ((1 << 16) | (5 << 8) | 0)) // only applicable before shoggoth (1.5.0)
    entity->setNormaliseNormals(true);
#endif
	entity->setCastShadows(true);

    entity->setMaterialName("Bullet/box");

    CylinderCollisionShape *sceneCubeShape = new CylinderCollisionShape(size, Ogre::Vector3::UNIT_X);

    RigidBody *defaultBody = new RigidBody(
        "defaultCylinderRigid" + StringConverter::toString(mNumEntitiesInstanced), 
        mWorld);

    SceneNode *node = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
    node->attachObject (entity);

    defaultBody->setShape (node, sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);

    mEntities.push_back(entity);
    mShapes.push_back(sceneCubeShape);
    mBodies.push_back(defaultBody);
    mNumEntitiesInstanced++;

    return defaultBody;
}
// -------------------------------------------------------------------------
RigidBody *OgreBulletListener::addCone(const Ogre::String instanceName,
                                       const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Vector3 &size,
                                       const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, 
                                       const Ogre::Real bodyMass)
{
    Entity *entity = mSceneMgr->createEntity(
        instanceName + StringConverter::toString(mNumEntitiesInstanced),
        //"Cone.mesh");
        "Mesh.mesh");

    entity->setQueryFlags (GEOMETRY_QUERY_MASK);
#if (OGRE_VERSION < ((1 << 16) | (5 << 8) | 0)) // only applicable before shoggoth (1.5.0)
    entity->setNormaliseNormals(true);
#endif
	entity->setCastShadows(true);

    entity->setMaterialName("Bullet/box");

    ConeCollisionShape *sceneCubeShape = new ConeCollisionShape(size.x, size.y, Ogre::Vector3::UNIT_Y);

    RigidBody *defaultBody = new RigidBody(
        "defaultConeRigid" + StringConverter::toString(mNumEntitiesInstanced), 
        mWorld);

    SceneNode *node = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
    node->attachObject (entity);

    defaultBody->setShape (node, sceneCubeShape, bodyRestitution, bodyFriction, bodyMass, pos, q);

    mEntities.push_back(entity);
    mShapes.push_back(sceneCubeShape);
    mBodies.push_back(defaultBody);
    mNumEntitiesInstanced++;

    return defaultBody;
}
// -------------------------------------------------------------------------
RigidBody *OgreBulletListener::addStaticTrimesh(const Ogre::String &instanceName,
                                                const Ogre::String &meshName,
                                                const Ogre::Vector3 &pos, 
                                                const Ogre::Quaternion &q, 
                                                const Ogre::Real bodyRestitution, 
                                                const Ogre::Real bodyFriction,
                                                bool castShadow)
{
    Entity *sceneEntity = mSceneMgr->createEntity(instanceName + StringConverter::toString(mNumEntitiesInstanced), meshName);
    sceneEntity->setCastShadows (castShadow);

    StaticMeshToShapeConverter *trimeshConverter = new StaticMeshToShapeConverter(sceneEntity);
    TriangleMeshCollisionShape *sceneTriMeshShape = trimeshConverter->createTrimesh();
    delete trimeshConverter;
    RigidBody *sceneRigid = new RigidBody(
        instanceName + "Rigid" + StringConverter::toString(mNumEntitiesInstanced),
        mWorld);

    SceneNode *node = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
    node->attachObject (sceneEntity);

    sceneRigid->setStaticShape(node, sceneTriMeshShape, bodyRestitution, bodyFriction, pos);

    mEntities.push_back(sceneEntity);
    mBodies.push_back(sceneRigid);
    mNumEntitiesInstanced++;

    return sceneRigid;
}
// -------------------------------------------------------------------------
RigidBody *OgreBulletListener::addStaticPlane( const Ogre::Real bodyRestitution, 
                                              const Ogre::Real bodyFriction)
{
    // Use a load of meshes to represent the floor
    int i = 0;
    StaticGeometry* s;
    s = mSceneMgr->createStaticGeometry("StaticFloor");
    s->setRegionDimensions(Ogre::Vector3(160.0, 100.0, 160.0));
    // Set the region origin so the center is at 0 world
    s->setOrigin(Ogre::Vector3::ZERO);
    for (Real z = -80.0;z <= 80.0;z += 20.0)
    {
        for (Real x = -80.0;x <= 80.0;x += 20.0)
        {
            String name = String("Plane_") + StringConverter::toString(i++);

            Entity* entity = mSceneMgr->createEntity(name, "plane.mesh");
			entity->setMaterialName("BulletPlane");
            entity->setQueryFlags (STATIC_GEOMETRY_QUERY_MASK);
            //entity->setUserObject(_plane);
            entity->setCastShadows(false);
            s->addEntity(entity, Ogre::Vector3(x,0,z));
        }
    }
    s->build();
    //SceneNode* mPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);


    CollisionShape *Shape = new StaticPlaneCollisionShape (Ogre::Vector3(0,1,0), 0);

    RigidBody *defaultPlaneBody = new RigidBody(
        "Plane" + StringConverter::toString(mNumEntitiesInstanced), 
        mWorld);


    defaultPlaneBody->setStaticShape (Shape, bodyRestitution, bodyFriction);

    mBodies.push_back(defaultPlaneBody);
    mShapes.push_back(Shape);

    mNumEntitiesInstanced++;

    return defaultPlaneBody;
}


// -------------------------------------------------------------------------
void OgreBulletListener::updateStats(void)
{

    // update stats when necessary
    if (mFpsStaticText)
    {
        const RenderTarget::FrameStats& stats = mWindow->getStatistics();

        static String avgFps = "Average FPS: ";
        static String currFps = "Current FPS: ";
        static String tris = "Triangle Count: ";


        mFpsStaticText->setValue
            (
            avgFps + StringConverter::toString(stats.avgFPS) + " / " +
            currFps + StringConverter::toString(stats.lastFPS) + " / " +
            tris + StringConverter::toString(stats.triangleCount)
            );
    }

    try {
        OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
        guiDbg->setCaption(mDebugText);
    }
    catch(...) {}
}
