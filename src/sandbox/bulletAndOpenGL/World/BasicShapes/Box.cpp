#include "Box.h"

Box::Box(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter, GLfloat w, GLfloat h, GLfloat l)
{
    this->w = w;
    this->h = h;
    this->l = l;

    // TODO remove membres
    this->xCenter = xCenter;
    this->yCenter = yCenter;
    this->zCenter = zCenter;

    // shape & material
    this->boxShape = new btBoxShape(btVector3(w/2.0,h/2.0,l/2.0));
    this->motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(xCenter,yCenter,zCenter)));

    btScalar mass = 5;

    setColor(0.34, 0.65, 0.17);


    if(w == 0.1)
        mass = 100000000;

    btVector3 fallInertia(0,0,0);
    this->boxShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,this->motionState,this->boxShape,fallInertia);
    this->rigidBody = new btRigidBody(fallRigidBodyCI);
}

void Box::draw()
{
    glColor3fv(color);

    glPushMatrix();

    // get the transform
    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);

    // position
    glTranslated(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

    // rotation
    glRotated(180 * trans.getRotation().getAngle() / 3.14, trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z());

    // scale
    glScaled(boxShape->getHalfExtentsWithMargin().getX(), boxShape->getHalfExtentsWithMargin().getY(), boxShape->getHalfExtentsWithMargin().getZ());

    // draw a unitary cube
    glBegin(GL_POLYGON);
        glNormal3i(0,0,1);
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, -1, 1);
        glVertex3d( 1, -1, 1);
        glVertex3d( 1, 1, 1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3i(0,0,-1);
        glVertex3d( 1, 1, -1);
        glVertex3d( 1, -1, -1);
        glVertex3d( -1, -1, -1);
        glVertex3d( -1, 1, -1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3i(1,0,0);
        glVertex3d( 1, 1, 1);
        glVertex3d( 1, -1, 1);
        glVertex3d( 1, -1, -1);
        glVertex3d( 1, 1, -1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3i(-1,0,0);
        glVertex3d( -1, 1, 1);
        glVertex3d( -1, 1, -1);
        glVertex3d( -1, -1, -1);
        glVertex3d( -1, -1, 1);
    glEnd();

    // top
    glBegin(GL_POLYGON);
        glNormal3i(0,-1,0);
        glVertex3d( -1, -1, 1);
        glVertex3d( -1, -1, -1);
        glVertex3d( 1, -1, -1);
        glVertex3d( 1, -1, 1);
    glEnd();

    // bottom
    glBegin(GL_POLYGON);
        glNormal3i(0,1,0);
        glVertex3d( -1, 1, 1);
        glVertex3d( 1, 1, 1);
        glVertex3d( 1, 1, -1);
        glVertex3d( -1, 1, -1);
    glEnd();

   glPopMatrix();
}
