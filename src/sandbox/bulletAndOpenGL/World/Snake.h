#ifndef SNAKE_H
#define SNAKE_H

#include "Drawable.h"
#include "Constraints/PointToPointConstraint.h"
#include "BasicShapes/Sphere.h"
#include "BasicShapes/Box.h"
#include "Bullet/btBulletDynamicsCommon.h"

const int NB_BOXES = 10;
const int NB_JOINTS = NB_BOXES-1;

class Snake : public Drawable
{
public :

    Box* boxes[NB_BOXES];
    PointToPointConstraint* pointToPointConstraints[NB_JOINTS];
    btGeneric6DofConstraint* generic6DofConstraints[NB_JOINTS];

    Box * bTest;

    // Constructor
    Snake(btDiscreteDynamicsWorld *dynamicsWorld)
    {

        btTransform tr;
        tr.setIdentity();
        tr.setOrigin(btVector3(btScalar(10.), btScalar(-15.), btScalar(0.)));

        bTest = new Box(1, 1, 1, 1, 1, 1);
        btRigidBody* pBody = bTest->rigidBody;
        //btRigidBody* pBody = localCreateRigidBody( 1.0, tr, shape);
        pBody->setActivationState(DISABLE_DEACTIVATION);
        btTransform frameB;
        frameB.setIdentity();
        btGeneric6DofConstraint* pGen6Dof = new btGeneric6DofConstraint( *pBody, frameB, false );
        dynamicsWorld->addConstraint(pGen6Dof);
        //pGen6Dof->setDbgDrawSize(btScalar(5.f));


        const btScalar PI = 3.14;
        pGen6Dof->setAngularLowerLimit(btVector3(180.0,0,180));
        pGen6Dof->setAngularUpperLimit(btVector3(-180.0,0,-180.0));

        //pGen6Dof->setLinearLowerLimit(btVector3(-10., 0, 0));
        //pGen6Dof->setLinearUpperLimit(btVector3(10., 0, 0));
        //pGen6Dof->getTranslationalLimitMotor()->m_enableMotor[0] = true;
        //pGen6Dof->getTranslationalLimitMotor()->m_targetVelocity[0] = 5.0f;
        //pGen6Dof->getTranslationalLimitMotor()->m_maxMotorForce[0] = 0.1f;

        pGen6Dof->getRotationalLimitMotor(0)->m_enableMotor = true;
        pGen6Dof->getRotationalLimitMotor(0)->m_targetVelocity = -50.0f;
        pGen6Dof->getRotationalLimitMotor(0)->m_maxMotorForce = 0.1f;

        pGen6Dof->getRotationalLimitMotor(2)->m_enableMotor = true;
        pGen6Dof->getRotationalLimitMotor(2)->m_targetVelocity = -50.0f;
        pGen6Dof->getRotationalLimitMotor(2)->m_maxMotorForce = 0.1f;



        dynamicsWorld->addRigidBody(pBody);
        //dynamicsWorld->addConstraint(pGen6Dof);





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

        // main constraint
        //btPoint2PointConstraint *ct = new btPoint2PointConstraint(*b->rigidBody, btVector3(-stickW/2.f-1,0,0));
        //dynamicsWorld->addConstraint(ct);




        btGeneric6DofConstraint *joint6DOF_x, *joint6DOF_y, *joint6DOF_z;
        btTransform localA, localB;
        bool useLinearReferenceFrameA = true;



        // add joint and new stick
        for(int i=0;i<NB_JOINTS;i++)
        {
            x += stickW+stickDistance;
            Box *bNext = new Box(x, y, z, stickW, stickH, stickL);


            localA.setIdentity();
            localB.setIdentity();
            localA.setOrigin(btVector3(stickW/2.f+stickDistance/2.0,0,0));
            localB.setOrigin(btVector3(-stickW/2.f-stickDistance/2.0,0,0));

            joint6DOF_x = new btGeneric6DofConstraint(*b->rigidBody, *bNext->rigidBody, localA, localB, useLinearReferenceFrameA);

            //joint6DOF_x->setAngularLowerLimit(btVector3(100.0,100,100));
            //joint6DOF_x->setAngularUpperLimit(btVector3(-100.0,-100,100));
            //joint6DOF_x->setAngularLowerLimit(btVector3(-SIMD_EPSILON, -SIMD_EPSILON, -SIMD_EPSILON));
            //joint6DOF_x->setAngularUpperLimit(btVector3(SIMD_EPSILON, SIMD_EPSILON, SIMD_EPSILON));

            generic6DofConstraints[i] = joint6DOF_x;


            /*
            joint6DOF_y = new btGeneric6DofConstraint(*b->rigidBody, *bNext->rigidBody, localA, localB, useLinearReferenceFrameA);
            joint6DOF_y->setAngularLowerLimit(btVector3(0.0, 1.0, 0));
            joint6DOF_y->setAngularUpperLimit(btVector3(0.0, 1.0, 0));

            joint6DOF_z = new btGeneric6DofConstraint(*b->rigidBody, *bNext->rigidBody, localA, localB, useLinearReferenceFrameA);
            joint6DOF_z->setAngularLowerLimit(btVector3(0, 0, 1.0));
            joint6DOF_z->setAngularUpperLimit(btVector3(0, 0, 1.0));
            */

            dynamicsWorld->addConstraint(joint6DOF_x,true); // add constraint AND disable collision between this 2 linked body
            //dynamicsWorld->addConstraint(joint6DOF_y,true); // add constraint AND disable collision between this 2 linked body
            //dynamicsWorld->addConstraint(joint6DOF_z,true); // add constraint AND disable collision between this 2 linked body


            //p2pc = new PointToPointConstraint(*b->rigidBody,*bNext->rigidBody,btVector3(stickW/2.f+stickDistance/2.0,0,0), btVector3(-stickW/2.f-stickDistance/2.0,0,0));
            //p2pc->addToDynamicsWorld(dynamicsWorld);

            //pointToPointConstraints[i] = p2pc;
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
       bTest->draw();

       for(int i=0;i<NB_BOXES;i++)
         boxes[i]->draw();

       /*
       for(int i=0;i<NB_JOINTS;i++)
         pointToPointConstraints[i]->draw();
        */
        /*
        b1->draw();
        b2->draw();
        //b3->draw();
        j->draw();*/
    }

    void jump()
    {

        for(int i=0;i<NB_JOINTS;i++)
        {
            /*
            generic6DofConstraints[i]->enable(3,true);
            generic6DofConstraints[i]->setStiffness(3,10);
            generic6DofConstraints[i]->getRotationalLimitMotor(3);
            */


            generic6DofConstraints[i]->getRigidBodyA().setActivationState(DISABLE_DEACTIVATION);
            generic6DofConstraints[i]->getRigidBodyB().setActivationState(DISABLE_DEACTIVATION);


            float t;
            if((i+1) % 2 == 0)
                t = -10.0f;
            else
                t = 10.0f;


            generic6DofConstraints[i]->getRotationalLimitMotor(1)->m_enableMotor = true;
            generic6DofConstraints[i]->getRotationalLimitMotor(1)->m_targetVelocity = t;
            generic6DofConstraints[i]->getRotationalLimitMotor(1)->m_maxMotorForce  = 10.0f;

/*
            generic6DofConstraints[i]->setDbgDrawSize(btScalar(5.f));
            generic6DofConstraints[i]->getTranslationalLimitMotor()->m_enableMotor[0] = true;
            generic6DofConstraints[i]->getTranslationalLimitMotor()->m_targetVelocity[0] = 5.0f;
            generic6DofConstraints[i]->getTranslationalLimitMotor()->m_maxMotorForce[0] = 0.1f;
*/
            qDebug() << generic6DofConstraints[i]->getRotationalLimitMotor(3)->needApplyTorques();
        }

        //b1->rigidBody->applyCentralImpulse(btVector3(0,1000,0));
    }

private :

    Box *b1,
        *b2;

    PointToPointConstraint *p2pc;
};

#endif // SNAKE_H
