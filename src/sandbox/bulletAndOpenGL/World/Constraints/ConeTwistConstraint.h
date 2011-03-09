#ifndef CONETWISTCONSTRAINT_H
#define CONETWISTCONSTRAINT_H

#include "../BasicShapes/Box.h"
#include "../Drawable.h"
#include "Bullet/LinearMath/btVector3.h"

class ConeTwistConstraint : public btConeTwistConstraint, public Drawable
{

private :

public :

        ConeTwistConstraint(btRigidBody& rbA,btRigidBody& rbB,const btTransform& rbAFrame, const btTransform& rbBFrame)
            : btConeTwistConstraint(rbA, rbB, rbAFrame, rbBFrame)
    {

    }

    void addToDynamicsWorld(btDynamicsWorld *dynamicsWorld)
    {
        // add the constraint into the world
        dynamicsWorld->addConstraint(this);
    }

    void draw()
    {

    }
};

#endif // CONETWISTCONSTRAINT_H
