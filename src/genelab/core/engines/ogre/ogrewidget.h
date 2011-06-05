#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <QGLWidget>
#include <QX11Info>
#include <QMutex>
#include <QMouseEvent>
#include "genelabcoreclasses.h"
#include "ogre/entities/ogrefreecamera.h"
#include <Ogre.h>
#include "entity.h"

namespace GeneLabCore {
    class OgreWidget : public QWidget
    {
        Q_OBJECT

    public:
        OgreWidget(Ogre::Root* ogreRoot,
                   Ogre::SceneManager* scnManager,
                   Ogre::Camera* camera,
                   QWidget *parent):
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

        void step();

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

    signals:
        // Events
        void mousePressed(QMouseEvent * e);
        void mouseReleased(QMouseEvent * e);
        void mouseMoved(QMouseEvent * e);
        void keyPressed(QKeyEvent *e);
        void keyReleased(QKeyEvent *e);
        void entered(QEvent * event);
        void leaved(QEvent * event);
        void stepped();

    protected:

        // Ogre
        Ogre::Root *mOgreRoot;
        Ogre::RenderWindow *mOgreWindow;
        Ogre::Camera *mCamera;
        Ogre::Viewport *mViewport;
        Ogre::SceneManager *mSceneMgr;

        bool mIsInit;
        static int ogrewidgetCpt;

        // Events
        void mousePressEvent(QMouseEvent * e);
        void mouseReleaseEvent(QMouseEvent * e);
        void mouseMoveEvent(QMouseEvent * e);
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);
        void enterEvent(QEvent * event);
        void leaveEvent(QEvent * event);

    private:

        OgreFreeCamera *ogreFreeCamera;
    };
}
#endif // OGREWIDGET_H
