#ifndef HUMAN_H
#define HUMAN_H

#include "Drawable.h"
#include "BasicShapes/Sphere.h"
#include "BasicShapes/Box.h"
#include "Bullet/btBulletDynamicsCommon.h"

class Human : public Drawable
{
public :

    Human(btDiscreteDynamicsWorld *dynamicsWorld)
    {
        // create members
        head        = new Sphere(0.f, 4.f, 0.f, 1.f);
        body        = new Box(0.f, 0.f, 0.f, 3.f, 4.f, 1.f);
        armLeft     = new Box(3.5f, 1.5f, 0.f, 2.f, 1.f, 1.f);
        armRight    = new Box(-3.5f, 1.5f, 0.f, 2.f, 1.f, 1.f);
        legLeft     = new Box(1.f, -4.5f, 0.f, 1.f, 4.f, 1.f);
        legRight    = new Box(-1.f, -4.5f, 0.f, 1.f, 4.f, 1.f);

        // colors
        head->setColor(0.2,0.2,0.2);
        body->setColor(0.0,0.0,1.0);
        armLeft->setColor(1.0,0.0,0.0);
        armRight->setColor(1.0,0.0,0.0);
        legLeft->setColor(0.0,1.0,0.0);
        legRight->setColor(0.0,1.0,0.0);

        // create physic constraints
        btPoint2PointConstraint *ctBodyHead = new btPoint2PointConstraint(*body->rigidBody, *head->rigidBody, btVector3(0,2.5,0), btVector3(0,-1,0));

        btPoint2PointConstraint *ctBodyArmLeft = new btPoint2PointConstraint(*body->rigidBody, *armLeft->rigidBody, btVector3(-2.5,1.5,0), btVector3(.5,0,0));
        btPoint2PointConstraint *ctBodyArmRight = new btPoint2PointConstraint(*body->rigidBody, *armRight->rigidBody, btVector3(2.5,1.5,0), btVector3(-.5,0,0));
        btPoint2PointConstraint *ctBodyLegLeft = new btPoint2PointConstraint(*body->rigidBody, *legLeft->rigidBody, btVector3(-1,-3.5,0), btVector3(0,1.5,0));
        btPoint2PointConstraint *ctBodyLegRight = new btPoint2PointConstraint(*body->rigidBody, *legRight->rigidBody, btVector3(1,-3.5,0), btVector3(0,1.5,0));

        // add physic constraints
        dynamicsWorld->addConstraint(ctBodyHead);
        dynamicsWorld->addConstraint(ctBodyArmLeft);
        dynamicsWorld->addConstraint(ctBodyArmRight);
        dynamicsWorld->addConstraint(ctBodyLegLeft);
        dynamicsWorld->addConstraint(ctBodyLegRight);

        // add to physic world
        dynamicsWorld->addRigidBody(head->rigidBody);
        dynamicsWorld->addRigidBody(body->rigidBody);
        dynamicsWorld->addRigidBody(armLeft->rigidBody);
        dynamicsWorld->addRigidBody(armRight->rigidBody);
        dynamicsWorld->addRigidBody(legLeft->rigidBody);
        dynamicsWorld->addRigidBody(legRight->rigidBody);
    }

    void draw()
    {
        head->draw();
        body->draw();
        armLeft->draw();
        armRight->draw();
        legLeft->draw();
        legRight->draw();
    }

    void jump()
    {
        body->rigidBody->applyCentralImpulse(btVector3(0,1000,0));
    }

private :

    Sphere *head;

    Box *body,
        *armLeft,
        *armRight,
        *legLeft,
        *legRight;
};

#endif // HUMAN_H
