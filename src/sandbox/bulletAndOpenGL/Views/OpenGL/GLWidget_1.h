#ifndef GLWIDGET_1_H
#define GLWIDGET_1_H

#include <QtOpenGL>
#include <QTimer>
#include <QKeyEvent>
#include <QMutex>
#include <cstdio>
#include "Camera.h"
#include "World/Drawable.h"
#include "World/BasicShapes/Box.h"
#include "World/BasicShapes/Axis.h"
#include "World/Human.h"
#include "Bullet/btBulletDynamicsCommon.h"

#define ANGLE_DE_VUE 90         // angle de vue
#define DIST_PROCH_V 0.1        // distance la plus proche visible
#define DIST_LOIN_V 12000       // angle la plus loins visible

class GLWidget_1 : public QGLWidget
{
    //Q_OBJECT

private:

    bool physicEnable;

    // Can't create de multiple heritage
    class Thread : public QThread
    {
    private:
        GLWidget_1 *parent;

    public:
        Thread( GLWidget_1 *parent )
        {
            this->parent = parent;
        }

        ///-- THREAD --///
        void run()
        {
            qDebug() << "HEllo";

            while(true)
            {
                parent->drawScene();
                msleep(10);
            }

            exec();
        }
    };

    GLfloat rtri, rquad;

    // Scene objects
    Human *human;
    Camera *camera;
    std::vector<Drawable*> drawableObjects;
    void addCameraView();

    // Physic engine
    btDiscreteDynamicsWorld* dynamicsWorld;

    // Protection
    QMutex mutex;

protected:

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

public:

    // Constructor
    GLWidget_1();

private slots:
    void simulate()
    {
        qDebug() << "toto";

        physicEnable = true;
    }

};

#endif // GLWIDGET_1_H
