#ifndef BOX_H
#define BOX_H

#include <QtOpenGL>
#include "../Drawable.h"
#include "Bullet/btBulletDynamicsCommon.h"

class Box : public Drawable
{
public :

    Box(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter, GLfloat w, GLfloat h, GLfloat l);

    void draw();

//private :

    GLfloat w,h,l;
    GLfloat xCenter, yCenter, zCenter, c;
    GLfloat aRot, xRot, yRot, zRot;

    btBoxShape* boxShape;
    btRigidBody* rigidBody;
    btDefaultMotionState* motionState;
};

#endif // BOX_H
