#ifndef HINGE_CONSTRAINT_H
#define HINGE_CONSTRAINT_H

#include "../BasicShapes/Box.h"
#include "../Drawable.h"
#include "Bullet/LinearMath/btVector3.h"

class HingeConstraint : public btHingeConstraint, public Drawable
{

private :

   GLfloat radius;

   void drawPivot(btRigidBody rigidBody, btVector3 pivot){

       glPushMatrix();

       // get the transformation
       btTransform trans;
       rigidBody.getMotionState()->getWorldTransform(trans);

       // position
       glTranslated(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

       // rotation
       glRotated(180 * trans.getRotation().getAngle() / 3.14, trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z());

       // move int local position
       glTranslated(pivot.getX(), pivot.getY(), pivot.getZ());

       // scale
       glScaled(radius, radius, radius);

       // draw sphere with glu
       gluSphere(gluNewQuadric(),radius,5,5);

       glPopMatrix();
   }

public :

        HingeConstraint(btRigidBody &rbA, btRigidBody &rbB,
                        btVector3 pivotInA, btVector3 pivotInB,
                        btVector3 &axisInA, btVector3 &axisInB,
                        bool useReferenceFrameA = false)
            : btHingeConstraint(rbA, rbB, pivotInA, pivotInB, axisInA, axisInB, useReferenceFrameA)
    {
        radius = 0.5;

        qDebug() << "Add HingeConstraint";

        // create physic constraints
        //ct = new btPoint2PointConstraint(rbA, rbB, pivotInA, pivotInB);
    }

    void addToDynamicsWorld(btDynamicsWorld *dynamicsWorld)
    {
        // add the constraint into the world
        dynamicsWorld->addConstraint(this);
    }

    void draw()
    {
        //glColor3fv(color);
        //drawPivot(this->getRigidBodyA(),this->getPivotInA());

        //glColor3fv(color);
        //drawPivot(this->getRigidBodyB(),this->getPivotInB());
    }
};

#endif // HINGE_CONSTRAINT_H
