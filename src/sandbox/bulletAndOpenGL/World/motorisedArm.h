#ifndef MOTORISEDARM_H
#define MOTORISEDARM_H

#include "Drawable.h"
#include "BasicShapes/Box.h"
#include "Bullet/btBulletDynamicsCommon.h"

class MotorisedArm : public Drawable
{
private :

    btGeneric6DofConstraint * constraints[1];
    Box *base, *biceps, *forearm;

    btGeneric6DofConstraint *baseConstraint;

public :

    // Constructor
    MotorisedArm()
    {
        // constraint
        btTransform localA, localB;
        bool useLinearReferenceFrameA = false;
        localA.setIdentity();
        localB.setIdentity();


        // Base (Socle)
        base = new Box(0,0,0,5,1,5);
        //base->rigidBody->setActivationState(DISABLE_DEACTIVATION);
        localA.setOrigin(btVector3(0,0,0));
        baseConstraint = new btGeneric6DofConstraint(*base->rigidBody, localA, useLinearReferenceFrameA);
        baseConstraint->setAngularLowerLimit(btVector3(0,0,0));
        baseConstraint->setAngularUpperLimit(btVector3(0,0,0));


        // Biceps (Arm)
        localA.setOrigin(btVector3(0.f,0.f,0.f));
        localB.setOrigin(btVector3(0.f,0.f,0.f));
        biceps = new Box(0,1,0,1,2,1);
        biceps->rigidBody->setActivationState(DISABLE_DEACTIVATION);

        biceps->rigidBody->setDamping(0.05f, 0.85f);
        biceps->rigidBody->setDeactivationTime(0.8f);
        biceps->rigidBody->setSleepingThresholds(1.6f, 2.5f);



//        btScalar mass = 1;
//        btVector3 fallInertia(0,0,0);
//        biceps->rigidBody->setMassProps(mass,fallInertia);
//        biceps->rigidBody->getCollisionShape()->calculateLocalInertia(mass,fallInertia);



        btGeneric6DofConstraint *joint6DOF = new btGeneric6DofConstraint(*biceps->rigidBody, localA, useLinearReferenceFrameA);
//      btGeneric6DofConstraint *joint6DOF = new btGeneric6DofConstraint(*base->rigidBody, *biceps->rigidBody, localA, localB, useLinearReferenceFrameA);

        joint6DOF->setLinearLowerLimit(btVector3(0,0,0));
        joint6DOF->setLinearUpperLimit(btVector3(0,0,0));
        joint6DOF->setAngularLowerLimit(btVector3(0,0,0));
        joint6DOF->setAngularUpperLimit(btVector3(0,0,0));

        constraints[0] = joint6DOF;



        // Forearm
//        localA.setOrigin(btVector3(0,1.f,0));
//        localB.setOrigin(btVector3(0,-1.5f,0));
//        forearm = new Box(0,3,0,1,2,1);
//        forearm->rigidBody->setActivationState(DISABLE_DEACTIVATION);
//        joint6DOF = new btGeneric6DofConstraint(*forearm->rigidBody, *base->rigidBody, localA, localB, useLinearReferenceFrameA);
//        joint6DOF->setAngularLowerLimit(btVector3(0,0,0));
//        joint6DOF->setAngularUpperLimit(btVector3(0,0,0));
//        constraints[1] = joint6DOF;
    }

    void addToWorld(btDiscreteDynamicsWorld *dynamicsWorld)
    {
//        dynamicsWorld->addRigidBody(base->rigidBody);
        dynamicsWorld->addRigidBody(biceps->rigidBody);
//        dynamicsWorld->addRigidBody(forearm->rigidBody);

//        dynamicsWorld->addConstraint(baseConstraint,false);

        // loop
        dynamicsWorld->addConstraint(constraints[0],false);
//        dynamicsWorld->addConstraint(constraints[1],false);
    }

    btGeneric6DofConstraint *getConstraint(int index)
    {
        return constraints[index];
    }

    void draw()
    {
//       base->draw();
       biceps->draw();
//       forearm->draw();
    }
};


#endif // MOTORISEDARM_H
