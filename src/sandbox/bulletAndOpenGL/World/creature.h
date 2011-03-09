#ifndef SNAKE_H
#define SNAKE_H

#include "Drawable.h"
#include "Joint.h"
#include "Sphere.h"
#include "Box.h"
#include "Bullet/btBulletDynamicsCommon.h"

class Snake : public Drawable
{
public :

    Snake(btDiscreteDynamicsWorld *dynamicsWorld)
    {

        const int NB_BOXES = 4;
        const int NB_JOINTS = NB_BOX-1;

        Box* boxes[NB_BOXES];
        Joint* joints[NB_JOINTS];

        // Snake ;)
        GLfloat stickW = 2.f, stickH = .2f, stickL = .2f;
        GLint x = 0, y = 0, z = 0;

        Box b = new Box(x, y, z, stickW, stickH, stickL);
        b->setColor(0.0,1.0,0.0);


        // creat
        for(int i=0;i<NB_JOINTS;i++)
        {
            x += stickW+1;
            Box bNext = new Box(x, y, z, stickW, stickH, stickL);

            j = new Joint(*b->rigidBody,*bNext->rigidBody,btVector3(-stickW,0,0), btVector3(stickW,0,0));
            j->addToDynamicsWorld(dynamicsWorld);

            joints[i] = j;
            boxes[i] = b;
            dynamicsWorld->addRigidBody(b->rigidBody);

            b = bNext;
        }

        boxes[NB_BOXES-1] = b;
        dynamicsWorld->addRigidBody(b->rigidBody);



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
         joints[i]->draw();

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

    Joint *j;
};

#endif // SNAKE_H
