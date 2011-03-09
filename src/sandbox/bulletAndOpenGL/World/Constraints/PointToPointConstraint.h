#ifndef POINT_TO_POINT_CONSTRAINT_H
#define POINT_TO_POINT_CONSTRAINT_H

#include "../BasicShapes/Box.h"
#include "../Drawable.h"
#include "Bullet/LinearMath/btVector3.h"

class PointToPointConstraint : public btPoint2PointConstraint, public Drawable
{

private :

   GLfloat radius;

   bool anchor;

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

    PointToPointConstraint(btRigidBody &rbA, btRigidBody &rbB, btVector3 pivotInA, btVector3 pivotInB)
        : btPoint2PointConstraint(rbA, rbB, pivotInA, pivotInB)
    {
        radius = 0.5;
        anchor = false;
        qDebug() << "Add PointToPointConstraint";
    }

    PointToPointConstraint(btRigidBody &rbA, btVector3 pivotInA)
        : btPoint2PointConstraint(rbA, pivotInA)
    {
        radius = 0.5;
        anchor = true;
        qDebug() << "Add PointToPointConstraint";
    }


    void addToDynamicsWorld(btDynamicsWorld *dynamicsWorld)
    {
        // add the constraint into the world
        dynamicsWorld->addConstraint(this);
    }

    void draw()
    {
        //glColor3fv(color);
        drawPivot(this->getRigidBodyA(),this->getPivotInA());

        //glColor3fv(color);
        if(!anchor)
            drawPivot(this->getRigidBodyB(),this->getPivotInB());
    }
};



#endif // JOINT_H
