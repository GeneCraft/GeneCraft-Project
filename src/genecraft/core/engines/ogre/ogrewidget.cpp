/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ogrewidget.h"
#include "Ogre.h"
#include "OgreViewport.h"
#include "bullet/bulletengine.h"
#include "ogre/ogreengine.h"

#if defined(Q_WS_X11)
  #include <QX11Info>
#endif
using namespace Ogre;

namespace GeneCraftCore {

    OgreWidget::OgreWidget(Ogre::Root* ogreRoot,
               Ogre::SceneManager* scnManager,
               Ogre::Camera* camera,
               QWidget *parent):
    QWidget( parent ),
        resized(true),
        mOgreRoot(ogreRoot),
        mOgreWindow(NULL),
        mCamera(NULL),
        mViewport(NULL),
        mSceneMgr(scnManager),
        mIsInit(false),
        ogreFreeCamera(NULL) {}

    OgreWidget::~OgreWidget() {
        destroy();
    }

    /**
     * @brief init the object
     * @author kito berg-taylor
     */
    int OgreWidget::ogrewidgetCpt = 0;
    void OgreWidget::init() {
        //These attributes are the same as those use in a QGLWidget
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_NoSystemBackground);

        //Parameters to pass to Ogre::Root::createRenderWindow()
        Ogre::NameValuePairList params;
        params["useNVPerfHUD"] = "true";

        //The external windows handle parameters are platform-specific
        Ogre::String externalWindowHandleParams;

        //Accept input focus
        setFocusPolicy(Qt::StrongFocus);

#if defined(Q_WS_WIN) || defined(Q_WS_MAC)
        //positive integer for W32 (HWND handle) - According to Ogre Docs
        externalWindowHandleParams = Ogre::StringConverter::toString((size_t)(winId()));
#endif

#if defined(Q_WS_X11)
        //poslong:posint:poslong:poslong (display*:screen:windowHandle:XVisualInfo*) for GLX - According to Ogre Docs
        QX11Info info = x11Info();
        externalWindowHandleParams  = Ogre::StringConverter::toString((unsigned long)(info.display()));
        externalWindowHandleParams += ":";
        externalWindowHandleParams += Ogre::StringConverter::toString((unsigned int)(info.screen()));
        externalWindowHandleParams += ":";
        externalWindowHandleParams += Ogre::StringConverter::toString((unsigned long)(this->parentWidget()->winId()));
        //    winHandle += Ogre::StringConverter::toString((unsigned long)(this->window()->winId()));
           //params["parentWindowHandle"] = winHandle;
#endif

        //Add the external window handle parameters to the existing params set.
#if defined(Q_WS_WIN) || defined(Q_WS_MAC)
        params["externalWindowHandle"] = externalWindowHandleParams;
#endif

#if defined(Q_WS_X11)
        params["parentWindowHandle"] = externalWindowHandleParams;
#endif

#if defined(Q_WS_MAC)
        params["macAPI"] = "cocoa";
        params["macAPICocoaUseNSView"] = "true";
#endif


         //Finally create our window.
        mOgreWindow = this->mOgreRoot->createRenderWindow(
                "OgreWindow" + QString::number(ogrewidgetCpt++).toStdString()
                , 640, 480, false, &params);

        mOgreWindow->setActive(true);
        WId ogreWinId = 0x0;
        mOgreWindow->getCustomAttribute( "WINDOW", &ogreWinId );


        //assert( ogreWinId );

#if defined(Q_WS_X11)
        // TAG: Build on linux
        create( ogreWinId );
#endif
        // Create the free camera (FIXME no encapsulation)
        if(mCamera == NULL){

            Ogre::Camera* cam1 = mSceneMgr->createCamera("firstCamera");
            cam1->setPosition(Ogre::Vector3(0, 2, 6));
            cam1->lookAt(Ogre::Vector3(0, 2, 0));
            cam1->setNearClipDistance(0.01); // 10 mm
            cam1->setFarClipDistance(5000); // 1km
            mCamera = cam1;
        }


        mViewport = mOgreWindow->addViewport( mCamera );
        mViewport->setBackgroundColour( Ogre::ColourValue( 0.5,0.5,1 ) );
        mViewport->setOverlaysEnabled(true);
        mIsInit = true;
        resized = true;


        ogreFreeCamera = new OgreFreeCamera(mCamera);

        connect(this,SIGNAL(keyPressed(QKeyEvent*)),ogreFreeCamera,SLOT(keyPressEvent(QKeyEvent*)));
        connect(this,SIGNAL(keyReleased(QKeyEvent*)),ogreFreeCamera,SLOT(keyReleaseEvent(QKeyEvent*)));
        connect(this,SIGNAL(mouseMoved(QMouseEvent*)),ogreFreeCamera,SLOT(mouseMoveEvent(QMouseEvent*)));
        connect(this,SIGNAL(mousePressed(QMouseEvent*)),ogreFreeCamera,SLOT(mousePressEvent(QMouseEvent*)));
        connect(this,SIGNAL(mouseReleased(QMouseEvent*)),ogreFreeCamera,SLOT(mouseReleaseEvent(QMouseEvent*)));
        connect(this,SIGNAL(entered(QEvent*)),ogreFreeCamera,SLOT(enterViewPortEvent(QEvent*)));
        connect(this,SIGNAL(leaved(QEvent*)),ogreFreeCamera,SLOT(leaveViewPortEvent(QEvent*)));
        connect(this,SIGNAL(stepped()),ogreFreeCamera,SLOT(step()));

    }

    void OgreWidget::resizeEvent(QResizeEvent *)
    {
        this->resized = true;

    }

    void OgreWidget::resize() {


/*         QString dimensions = QString( "%1x%2" )
                           .arg(this->width())
                 .arg(height());
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

    void OgreWidget::mousePressEvent(QMouseEvent *e) {
        emit mousePressed(new QMouseEvent(*e));
    }

    void OgreWidget::mouseReleaseEvent(QMouseEvent *e) {
        emit mouseReleased(new QMouseEvent(*e));
    }

    void OgreWidget::mouseMoveEvent(QMouseEvent *e) {
        emit mouseMoved(new QMouseEvent(*e));
    }

    void OgreWidget::keyPressEvent(QKeyEvent *e) {
        emit keyPressed(new QKeyEvent(*e));
    }

    void OgreWidget::keyReleaseEvent(QKeyEvent *e) {
        emit keyReleased(new QKeyEvent(*e));
    }

    void OgreWidget::enterEvent (QEvent *e) {
        emit entered(new QEvent(*e));
    }

    void OgreWidget::leaveEvent (QEvent *e) {
        emit leaved(new QEvent(*e));
    }

    void OgreWidget::step() {
        emit stepped();
    }
}
