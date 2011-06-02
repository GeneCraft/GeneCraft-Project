#include "ant.h"

#include "btshapesfactory.h"
#include "fixation.h"
#include "bone.h"
#include "treeshape.h"
#include "entity.h"
#include "LinearMath/btQuaternion.h"

namespace GeneLabCore {

Ant::Ant() : EntityFamily()
{
    nbLegs      = 6;
    nbBoneInLeg = 3;
    legRadius   = 0.2;
    legLenght   = 1.0;
    kneeRadius  = 0.35;
}

Entity* Ant::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {
    this->shapesFactory = shapesFactory;
    this->initialPosition = position;

    Entity* ent = new Entity("Ant", "AntFamily", 1);

    // root fixation
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(initialPosition);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,btScalar(0.6),initTransform);
    shape->setRoot(rootFix);
    ent->setShape(shape);

    // legs
    btQuaternion legLocal;
    legLocal.setEulerZYX(0,0,0);
    btVector3 lowerLimits(0,0,0);
    btVector3 upperLimits(0,0,0);

    btQuaternion local;

    local.setEulerZYX(M_PI/2.0,0,0);
    Bone * bone = rootFix->addBone(0, M_PI/2.0f, 0.5, 0.5, 0.5, lowerLimits, upperLimits);

    for(int i=0;i<3;++i)
    {
        legLocal.setEulerZYX(0,0, M_PI / 6.0f * i + M_PI / 3.0);
        addLeg(bone->getEndFixation(),M_PI / 2.0f, M_PI / 6.0f * i + M_PI / 3.0,lowerLimits,upperLimits);
    }


    for(int i=0;i<3;++i)
    {
        legLocal.setEulerZYX(0,0, - M_PI / 6.0f * i - M_PI / 3.0);
        addLeg(bone->getEndFixation(),M_PI / 2.0, -M_PI / 6.0f * i - M_PI / 3.0,lowerLimits,upperLimits);
    }


    local.setEulerZYX(0,0,0);
    bone = bone->getEndFixation()->addBone(0,0,0.5,0.5,1,lowerLimits,upperLimits);



    return ent;
}

void Ant::addLeg(Fixation *fixBody, btScalar yAxis, btScalar zAxis, const btVector3 &lowerLimits, const btVector3 &upperLimits)
{
    Bone *rootBone = fixBody->addBone(yAxis, zAxis,
                                      btScalar(legRadius),
                                      btScalar(legLenght),
                                      btScalar(kneeRadius),
                                      lowerLimits,upperLimits);




    for(int i=1;i<nbBoneInLeg;++i)
    {
        btVector3 lowerLimits(-M_PI/4,0,-M_PI/12);
        btVector3 upperLimits(M_PI/4,0,M_PI/12);
        btQuaternion local;
        local.setEulerZYX(M_PI/6.0,0,0);

        rootBone = rootBone->getEndFixation()->addBone(-yAxis, M_PI / 6,
                                                       btScalar(legRadius - legRadius*(i/nbBoneInLeg)),
                                                       btScalar(legLenght - legLenght*(i/nbBoneInLeg)),
                                                       btScalar(kneeRadius),
                                                       lowerLimits,
                                                       upperLimits);
        yAxis = 0;
        //rootBone->getParentConstraint()->setAngularLowerLimit(btVector3(0,0,0));
        //rootBone->getParentConstraint()->setAngularUpperLimit(btVector3(0,0,0));
    }
}

QVariant Ant::serialize() {
    return QVariant();
}
}
