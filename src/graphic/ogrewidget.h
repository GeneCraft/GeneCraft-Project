#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <QGLWidget>
#include <QX11Info>
#include <QMutex>

#include "classes.h"

namespace GeneLabOgreBullet {
    class OgreWidget : public QWidget
    {
       Q_OBJECT

       public:
        OgreWidget(Ogre::Root* ogreRoot,
                   Ogre::SceneManager* scnManager,
                   Ogre::Camera* camera,
                   QWidget *parent=0 ):
          QWidget( parent ),
          mOgreWindow(NULL)
          {

            mOgreRoot = ogreRoot;
            mSceneMgr = scnManager;
            mCamera = camera;
            mIsInit = false;
            resized = true;
          }

        virtual ~OgreWidget()
          {
            destroy();
          }
    public:
        bool resized;
    public slots:

        void resize();
        void init();
        void resizeEvent(QResizeEvent* evt);
        QPaintEngine *paintEngine() const
        {
                return 0;
        }

        void paintEvent(QPaintEvent* evt)
        {
        }


       protected:
        Ogre::Root *mOgreRoot;
        Ogre::RenderWindow *mOgreWindow;
        Ogre::Camera *mCamera;
        Ogre::Viewport *mViewport;
        Ogre::SceneManager *mSceneMgr;

        bool mIsInit;
        static int ogrewidgetCpt;
    };
}
#endif // OGREWIDGET_H
