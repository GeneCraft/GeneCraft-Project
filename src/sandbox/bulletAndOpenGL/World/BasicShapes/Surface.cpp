
#include "Surface.h"

Surface::Surface(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter, GLfloat c)
{
    this->xCenter = xCenter;
    this->yCenter = yCenter;
    this->zCenter = zCenter;

    this->c = c;

    // shape & material
    this->collisionShape = new btStaticPlaneShape(btVector3(0,1,0),1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(xCenter,yCenter,zCenter)));
    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(0,groundMotionState,this->collisionShape,btVector3(0,0,0));

    this->rigidBody = new btRigidBody(groundRigidBodyCI);
    rigidBody->setDamping(0.1,0.0);
    rigidBody->setRestitution(0.5);
    rigidBody->setFriction(0.5);
}

void Surface::draw()
{
    glColor3f(.9,.9,.9);

    GLfloat x1 = xCenter - c / 2.0;
    GLfloat y1 = yCenter;
    GLfloat z1 = zCenter - c / 2.0;

    GLfloat x2 = xCenter + c / 2.0;
    GLfloat z2 = zCenter + c / 2.0;

    // chapeau
    glBegin(GL_QUADS);
        glNormal3i(0,1,0);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y1,z1);
        glVertex3f(x2,y1,z2);
        glVertex3f(x1,y1,z2);
    glEnd();
}

