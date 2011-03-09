#ifndef SURFACE_H
#define SURFACE_H

#include <QtOpenGL>
#include "../Drawable.h"
#include "Bullet/btBulletDynamicsCommon.h"

class Surface : public Drawable
{
    public :
        GLfloat xCenter, yCenter, zCenter, c;

        Surface(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter, GLfloat c);

        void draw();

        btCollisionShape* collisionShape;
        btRigidBody* rigidBody;
};

#endif // SURFACE_H
