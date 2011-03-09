#ifndef ARM_H
#define ARM_H

#include "Drawable.h"
#include "Constraints/PointToPointConstraint.h"
#include "Constraints/HingeConstraint.h"
#include "BasicShapes/Sphere.h"
#include "BasicShapes/Box.h"
#include "Bullet/btBulletDynamicsCommon.h"

class Arm : public Drawable
{
public :

    // Constructor
    Arm(btDiscreteDynamicsWorld *dynamicsWorld)
    {
        b1 = new Box(-4,0,0,4,1,1);
        b2 = new Box(4,0,0,4,1,1);

        btVector3 axisInA(0,0,1), axisInB(0,1,0);

        ct = new HingeConstraint(*b1->rigidBody,*b2->rigidBody,btVector3(3,0,0),btVector3(-3,0,0),axisInA,axisInB);

        // anchor
        //anchor = new PointToPointConstraint(*b1->rigidBody,btVector3(-3,0,0));

        // add the constraint into the world
        dynamicsWorld->addConstraint(ct);
        //dynamicsWorld->addConstraint(anchor);

        dynamicsWorld->addRigidBody(b1->rigidBody);
        dynamicsWorld->addRigidBody(b2->rigidBody);
    }

    void draw()
    {
       b1->draw();
       b2->draw();
       ct->draw();
       //anchor->draw();
    }

    void jump()
    {
        b1->rigidBody->applyCentralImpulse(btVector3(0,1000,0));
    }

    void contractA()
    {
        if(ct->getEnableAngularMotor())
            ct->enableMotor(false);
        else
            ct->enableAngularMotor(true,1,1);

        qDebug()<<"contract";
        //ct->
    }

    void contractB()
    {
       /* if(ct->getEnableAngularMotor())
            ct->enableMotor(false);
        else*/
            ct->enableAngularMotor(true,-10,-10);

        qDebug()<<"contract";
        //ct->
    }

private :

    Box *b1,
        *b2;

    HingeConstraint *ct;
    PointToPointConstraint *anchor;
};

#endif // ARM_H
