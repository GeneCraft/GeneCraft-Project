#include "ogrewidget.h"
#include "OGRE/Ogre.h"
#include <QDebug>
#include "bulletengine.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "OGRE/Ogre.h"
#include "ogreengine.h"

using namespace Ogre;

namespace GeneLabCore {

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

        connect(this,SIGNAL(keyPressed(QKeyEvent*)),ogreFreeCamera,SLOT(keyPressEvent(QKeyEvent*)));
        connect(this,SIGNAL(keyReleased(QKeyEvent*)),ogreFreeCamera,SLOT(keyReleaseEvent(QKeyEvent*)));
        connect(this,SIGNAL(mouseMoved(QMouseEvent*)),ogreFreeCamera,SLOT(mouseMoveEvent(QMouseEvent*)));
        connect(this,SIGNAL(mousePressed(QMouseEvent*)),ogreFreeCamera,SLOT(mousePressEvent(QMouseEvent*)));
        connect(this,SIGNAL(mouseReleased(QMouseEvent*)),ogreFreeCamera,SLOT(mouseReleaseEvent(QMouseEvent*)));
        connect(this,SIGNAL(entered(QEvent*)),ogreFreeCamera,SLOT(enterViewPortEvent(QEvent*)));
        connect(this,SIGNAL(leaved(QEvent*)),ogreFreeCamera,SLOT(leaveViewPortEvent(QEvent*)));
        connect(this,SIGNAL(stepped()),ogreFreeCamera,SLOT(step()));

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
        //ogreFreeCamera->mousePressEvent(e);
        emit mousePressed(new QMouseEvent(*e));
    }

    void OgreWidget::mouseReleaseEvent(QMouseEvent *e)
    {
        //ogreFreeCamera->mouseReleaseEvent(e);
        emit mouseReleased(new QMouseEvent(*e));
    }

    void OgreWidget::mouseMoveEvent(QMouseEvent *e)
    {
        //ogreFreeCamera->mouseMoveEvent(e);
        emit mouseMoved(new QMouseEvent(*e));
    }

    void OgreWidget::keyPressEvent(QKeyEvent *e)
    {
        //ogreFreeCamera->keyPressEvent(e);
        emit keyPressed(new QKeyEvent(*e));
    }

    void OgreWidget::keyReleaseEvent(QKeyEvent *e)
    {
        //ogreFreeCamera->keyReleaseEvent(e);
        emit keyReleased(new QKeyEvent(*e));
    }

    void OgreWidget::enterEvent (QEvent *e)
    {
        //ogreFreeCamera->enterViewPortEvent(e);
        emit entered(new QEvent(*e));
    }

    void OgreWidget::leaveEvent (QEvent *e)
    {
        //ogreFreeCamera->leaveViewPortEvent(e);
        emit leaved(new QEvent(*e));
    }

    void OgreWidget::step()
    {
        //ogreFreeCamera->step();
        emit stepped();
    }
}
