
#include "Sphere.h"

Sphere::Sphere(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter, GLfloat radius)
{
    //qDebug() << radius ;

    this->radius = radius;

    setColor(1.0,0.0,0.0);

    // Sphere
    collisionShape = new btSphereShape(radius);
    btDefaultMotionState* fallMotionState =
            new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(xCenter,yCenter,zCenter)));
    btScalar mass = 10;
    btVector3 fallInertia(0,0,0);
    collisionShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,collisionShape,fallInertia);
    rigidBody = new btRigidBody(fallRigidBodyCI);
    rigidBody->setDamping(0.1,0.0);
    rigidBody->setRestitution(0.5);
    rigidBody->setFriction(0.5);


}

void Sphere::draw()
{
    glColor3fv(color);

    glPushMatrix();

    // get the transformation
    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);

    // position
    glTranslated(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

    // rotation
    glRotated(180 * trans.getRotation().getAngle() / 3.14, trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z());

    // scale
    glScaled(radius, radius, radius);

    // draw sphere with glu
    gluSphere(gluNewQuadric(),1,radius*5,radius*5);

    glPopMatrix();
}

