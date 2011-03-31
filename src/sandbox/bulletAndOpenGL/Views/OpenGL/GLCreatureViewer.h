#ifndef GLCREATUREVIEWER_H
#define GLCREATUREVIEWER_H

#include <QtOpenGL>
#include <QTimer>
#include <QKeyEvent>
#include <QMutex>
#include <cstdio>
#include "Camera.h"
#include "World/Drawable.h"
#include "World/BasicShapes/Box.h"
#include "World/BasicShapes/Axis.h"
#include "World/BasicShapes/Sphere.h"
#include "World/BasicShapes/Surface.h"
#include "World/BasicShapes/drawablevector.h"
#include "World/Human.h"
#include "World/Snake.h"
#include "World/Arm.h"
#include "World/motorisedArm.h"
#include "Bullet/btBulletDynamicsCommon.h"


#define ANGLE_DE_VUE 90         // angle de vue
#define DIST_PROCH_V 0.1        // distance la plus proche visible
#define DIST_LOIN_V 12000       // angle la plus loins visible

class GLCreatureViewer : public QGLWidget
{
    Q_OBJECT

private:

    bool physicEnable;

    // Can't create de multiple heritage
    class Thread : public QThread
    {
    private:
        GLCreatureViewer *parent;

    public:
        Thread( GLCreatureViewer *parent )
        {
            this->parent = parent;
        }

        ///-- THREAD --///
        void run()
        {
            qDebug() << ">> Refresh thread start.";

            while(true)
            {
                parent->drawScene();
                msleep(10);
            }

            exec();
        }
    };

    GLfloat rtri, rquad;
    Camera *camera;
    std::vector<Drawable*> drawableObjects;
    btDiscreteDynamicsWorld* dynamicsWorld;

    Human *human;
    Snake *snake;
    Arm *arm;

protected:
    QMutex mutex;

    // OpenGL Tools
    void drawScene();

    // OpenGLWidget
    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();
    void timeOut();

    // Events
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);

    bool focused;


     MotorisedArm * motorisedArm;

public:
    // Constructor
    GLCreatureViewer();

    MotorisedArm * getMotorisedArm()
    {
        return motorisedArm;
    }

public slots:
    void refresh()
    {
        physicEnable = true;
    }
};

#endif // GLCREATUREVIEWER_H


