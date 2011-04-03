#include "ogrewidget.h"
#include "OGRE/Ogre.h"
#include <QDebug>
#include "physics/bulletmanager.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "OGRE/Ogre.h"
#include "graphic/ogremanager.h"

using namespace Ogre;

namespace GeneLabOgreBullet {

    /**
     * @brief init the object
     * @author kito berg-taylor
     */
    int OgreWidget::ogrewidgetCpt = 0;
    void OgreWidget::init() {
        qDebug() << "init !";
        //These attributes are the same as those use in a QGLWidget
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_NoSystemBackground);

        //Parameters to pass to Ogre::Root::createRenderWindow()
        Ogre::NameValuePairList params;
        //params["useNVPerfHUD"] = "true";

        //The external windows handle parameters are platform-specific
        Ogre::String externalWindowHandleParams;

        //Accept input focus
        setFocusPolicy(Qt::StrongFocus);

#if defined(Q_WS_WIN) || defined(Q_WS_MAC)
        //positive integer for W32 (HWND handle) - According to Ogre Docs
        externalWindowHandleParams = Ogre::StringConverter::toString((unsigned int)(this->parentWidget()->winId()));
#endif

#if defined(Q_WS_X11)
        //poslong:posint:poslong:poslong (display*:screen:windowHandle:XVisualInfo*) for GLX - According to Ogre Docs
        QX11Info info = x11Info();
        externalWindowHandleParams  = Ogre::StringConverter::toString((unsigned long)(info.display()));
        externalWindowHandleParams += ":";
        externalWindowHandleParams += Ogre::StringConverter::toString((unsigned int)(info.screen()));
        externalWindowHandleParams += ":";
        externalWindowHandleParams += Ogre::StringConverter::toString((unsigned long)(winId()));
        //externalWindowHandleParams += ":";
        //externalWindowHandleParams += Ogre::StringConverter::toString((unsigned long)(info.visual()));
#endif

        //Add the external window handle parameters to the existing params set.
#if defined(Q_WS_WIN) || defined(Q_WS_MAC)
        params["parentWindowHandle"] = externalWindowHandleParams;
#endif

#if defined(Q_WS_X11)
        params["parentWindowHandle"] = externalWindowHandleParams;
#endif

#if defined(Q_WS_MAC)
        params["macAPI"] = "cocoa";
        params["macAPICocoaUseNSView"] = "true";
#endif

        qDebug() << "init !";
        //Finally create our window.
        mOgreWindow = this->mOgreRoot->createRenderWindow(
                "OgreWindow" + QString::number(ogrewidgetCpt++).toStdString()
                , 640, 480, false, &params);

        mOgreWindow->setActive(true);
        WId ogreWinId = 0x0;
        mOgreWindow->getCustomAttribute( "WINDOW", &ogreWinId );

        qDebug() << "init !";
        assert( ogreWinId );

        this->create( ogreWinId );

        mViewport = mOgreWindow->addViewport( mCamera );
        mViewport->setBackgroundColour( Ogre::ColourValue( 0.8,0.8,1 ) );

        mIsInit = true;
        resized = true;


        // Create the free camera (FIXME no encapsulation)
        ogreFreeCamera = new OgreFreeCamera(mCamera);


        qDebug() << "init !";
    }

    /**
     * @brief resize the GL window
     * @author Kito Berg-Taylor
     */
    void OgreWidget::resizeEvent(QResizeEvent * e)
    {
        this->resized = true;

    }

    void OgreWidget::resize() {

        /*qDebug() << "resized !";
         QString dimensions = QString( "%1x%2" )
                           .arg(width)
                           .arg(height);
         Ogre::RenderSystem *renderSystem = mOgreRoot->getRenderSystem();
         renderSystem->setConfigOption( "Video Mode", dimensions.toStdString() );
       */
        this->resized = false;
        assert( mOgreWindow );
        mOgreWindow->windowMovedOrResized();
        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(
                Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));

    }

    void OgreWidget::mousePressEvent(QMouseEvent *e)
    {

        // Catch Camera events
        ogreFreeCamera->mousePressEvent(e);


//        qDebug() << "adding a box !";

//        Ogre::Vector3 size = Ogre::Vector3::ZERO;	// size of the box

//        // starting position of the box
//        Ogre::Vector3 position = (mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 10);

//        // create an ordinary, Ogre mesh with texture
//        Entity *entity = mSceneMgr->createEntity(
//                        "Box_" + StringConverter::toString(1),
//                        "cube.mesh");

//        entity->setCastShadows(true);

//        qDebug() << "entity created";

//        // we need the bounding box of the box to be able to set the size of the Bullet-box
//        AxisAlignedBox boundingB = entity->getBoundingBox();
//        size = boundingB.getSize(); size /= 2.0f; // only the half needed
//        size *= 0.95f;	// Bullet margin is a bit bigger so we need a smaller size
//                                                        // (Bullet 2.76 Physics SDK Manual page 18)
//        entity->setMaterialName("Examples/Rockwall");
//        entity->setCastShadows(true);

//        qDebug() << "material too";

//        SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//        node->attachObject(entity);
//        node->scale(0.05f, 0.05f, 0.05f); // the cube is too big for us
//        size *= 0.05f;			  // don't forget to scale down the Bullet-box too

//        qDebug() << "attached !";

//        // after that create the Bullet shape with the calculated size
//        OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);

//        // and the Bullet rigid body
//        OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
//                        "defaultBoxRigid_" + StringConverter::toString(1),
//                        mWorld);

//        defaultBody->setShape(	node,
//                                sceneBoxShape,
//                                0.6f,			// dynamic body restitution
//                                0.6f,			// dynamic body friction
//                                1.0f, 			// dynamic bodymass
//                                position,		// starting position of the box
//                                Quaternion(0,0,0,1));// orientation of the box

//        mNumEntitiesInstanced++;

//        qDebug() << "shape ok";

//        defaultBody->setLinearVelocity(
//                                mCamera->getDerivedDirection().normalisedCopy() * 7.0f ); // shooting speed


//        qDebug() << "velocity too";

//        // push the created objects to the dequese
//        mShapes.push_back(sceneBoxShape);
//        mBodies.push_back(defaultBody);

//        qDebug() << "end";

    }

    void OgreWidget::mouseReleaseEvent(QMouseEvent *e)
    {
        ogreFreeCamera->mouseReleaseEvent(e);
    }

    void OgreWidget::mouseMoveEvent(QMouseEvent *e)
    {
        ogreFreeCamera->mouseMoveEvent(e);
    }

    void OgreWidget::keyPressEvent(QKeyEvent *e)
    {
        ogreFreeCamera->keyPressEvent(e);
    }

    void OgreWidget::keyReleaseEvent(QKeyEvent *e)
    {
        ogreFreeCamera->keyReleaseEvent(e);
    }

    void OgreWidget::enterEvent (QEvent *e)
    {
        ogreFreeCamera->enterViewPortEvent(e);
    }

    void OgreWidget::leaveEvent (QEvent *e)
    {
        ogreFreeCamera->leaveViewPortEvent(e);
    }

    void OgreWidget::step()
    {
        ogreFreeCamera->step();
    }
}
