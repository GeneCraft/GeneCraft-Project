#ifndef SPHERE_H
#define SPHERE_H

#include <QtOpenGL>
#include "../Drawable.h"
#include "Bullet/btBulletDynamicsCommon.h"

class Sphere : public Drawable
{
public :

    Sphere(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter, GLfloat radius);

    void draw();

//private :

    GLfloat radius;

    btCollisionShape* collisionShape;
    btRigidBody* rigidBody;
    btDefaultMotionState* motionState;
};

#endif // SPHERE_H
