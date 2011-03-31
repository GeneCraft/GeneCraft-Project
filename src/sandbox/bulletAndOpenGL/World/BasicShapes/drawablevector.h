#ifndef DRAWABLEVECTOR_H
#define DRAWABLEVECTOR_H

#include <QtOpenGL>
#include "../Drawable.h"
#include "Bullet/btBulletDynamicsCommon.h"

class DrawableVector : public Drawable
{
public:

    btVector3 vector, point;

    DrawableVector(btVector3 vector, btVector3 point)
    {
        this->vector = vector;
        this->point = point;
    }

    void draw()
    {
        glPushMatrix();

        // position
        glTranslated(point.x(), point.y(), point.z());

        // rotation
        //glRotated(180 * trans.getRotation().getAngle() / 3.14, trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z());

        // draw
        glBegin(GL_LINES);
            glVertex3f( 0, 0, 0);
            glVertex3f( vector.x(), vector.y(), vector.z());
        glEnd();

        glPopMatrix();

    }
};

#endif // DRAWABLEVECTOR_H
