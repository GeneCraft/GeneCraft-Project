#ifndef SNAKE_H
#define SNAKE_H

#include "Drawable.h"
#include "Constraints/PointToPointConstraint.h"
#include "BasicShapes/Sphere.h"
#include "BasicShapes/Box.h"
#include "Bullet/btBulletDynamicsCommon.h"


const int NB_BOXES = 20;
const int NB_JOINTS = NB_BOXES-1;

class Snake : public Drawable
{
public :

    Box* boxes[NB_BOXES];
    PointToPointConstraint* pointToPointConstraints[NB_JOINTS];

    // Constructor
    Snake(btDiscreteDynamicsWorld *dynamicsWorld)
    {
        //NB_BOXES = 4;
        //NB_JOINTS = NB_BOXES-1;

        /*
        boxes = malloc( NB_BOXES * sizeof( Box* ) );
        joints = malloc( NB_JOINTS * sizeof( Joint* ) );
        */

        GLfloat stickDistance = .5f;
        GLfloat stickW = .5f, stickH = .1f, stickL = .1f;
        GLint x = 0, y = 40, z = 0;

        Box *b = new Box(x, y, z, stickW, stickH, stickL);
        b->setColor(0.0,1.0,0.0);

        btPoint2PointConstraint *ct = new btPoint2PointConstraint(*b->rigidBody, btVector3(-stickW/2.f-1,0,0));

        // add the constraint into the world
        dynamicsWorld->addConstraint(ct);

        // add joint and new stick
        for(int i=0;i<NB_JOINTS;i++)
        {
            x += stickW+stickDistance;
            Box *bNext = new Box(x, y, z, stickW, stickH, stickL);

            p2pc = new PointToPointConstraint(*b->rigidBody,*bNext->rigidBody,btVector3(stickW/2.f+stickDistance/2.0,0,0), btVector3(-stickW/2.f-stickDistance/2.0,0,0));
            p2pc->addToDynamicsWorld(dynamicsWorld);

            pointToPointConstraints[i] = p2pc;
            boxes[i] = b;
            dynamicsWorld->addRigidBody(b->rigidBody);

            b = bNext;
        }

        // add the last stick
        boxes[NB_BOXES-1] = b;
        dynamicsWorld->addRigidBody(b->rigidBody);


/// OLD


        // create members
        /*
        b1        = new Box(2.f, 0.f, 0.f, 2.f, .2f, .2f);
        b2        = new Box(-2.f, 0.f, 0.f, 2.f, .2f, .2f);
        b3        = new Box(0.f, 0.f, 0.f, 1.f, 1.f, 1.f);

        // colors
        b1->setColor(0.0,1.0,0.0);
        b2->setColor(1.0,1.0,0.0);
        b3->setColor(0.0,1.0,1.0);

        j = new Joint(*b1->rigidBody,*b2->rigidBody,btVector3(-2,0,0), btVector3(2,0,0));
        j->addToDynamicsWorld(dynamicsWorld);

        j = new Joint(*b1->rigidBody,*b3->rigidBody,btVector3(-1,0,0), btVector3(1,0,0));
        j->addToDynamicsWorld(dynamicsWorld);
*/
        /*
        // create physic constraints
        btTypedConstraint *ct = new btPoint2PointConstraint(*b1->rigidBody, *b2->rigidBody, btVector3(4,0,0), btVector3(-4,0,0));

        // add physic constraints
        dynamicsWorld->addConstraint(ct);
        */

        // add to physic world
        //dynamicsWorld->addRigidBody(b1->rigidBody);
        //dynamicsWorld->addRigidBody(b2->rigidBody);
        //dynamicsWorld->addRigidBody(b3->rigidBody);
    }

    void draw()
    {
       for(int i=0;i<NB_BOXES;i++)
         boxes[i]->draw();

       for(int i=0;i<NB_JOINTS;i++)
         pointToPointConstraints[i]->draw();

        /*
        b1->draw();
        b2->draw();
        //b3->draw();
        j->draw();*/
    }

    void jump()
    {
        b1->rigidBody->applyCentralImpulse(btVector3(0,1000,0));
    }

private :

    Box *b1,
        *b2;

    PointToPointConstraint *p2pc;
};

#endif // SNAKE_H
