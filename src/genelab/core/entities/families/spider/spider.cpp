#include "spider.h"
#include "btshapesfactory.h"
#include "fixation.h"
#include "bone.h"

namespace GeneLabCore {

#define PI 3.14159265

Spider::Spider(btShapesFactory *shapesFactory, const btVector3 &position) :
    Entity("Spider","SpiderFamily",1), shapesFactory(shapesFactory), initialPosition(position)
{
    nbLegs      = 8;
    nbBoneInLeg = 2;
    legRadius   = 0.3;
    legLenght   = 2;
    kneeRadius  = 0.35;

    // root fixation
    rootFix = new Fixation(shapesFactory,btScalar(1.0),initialPosition);
    rootFix->setEntity(this);

    // legs
    btTransform legLocal;
    btVector3 lowerLimits(0,0,0);
    btVector3 upperLimits(0,0,0);

    for(int i=0;i<nbLegs;++i)
    {
        legLocal.setIdentity();
        legLocal.getBasis().setEulerZYX(i*(2.0*PI/nbLegs),0,PI / 2.0);
        legLocal.setOrigin(btVector3(0,0,0));
        addLeg(rootFix,legLocal,lowerLimits,upperLimits);
    }
}

void Spider::addLeg(Fixation *fixBody, const btTransform &localFix, const btVector3 &lowerLimits, const btVector3 &upperLimits)
{
    Bone *rootBone = fixBody->addBone(localFix,btScalar(legRadius),btScalar(legLenght),btScalar(kneeRadius),lowerLimits,upperLimits);

    for(int i=1;i<nbBoneInLeg;++i)
    {
        btTransform local; local.setIdentity();
        local.getBasis().setEulerZYX(0,0,PI/2.0);
        rootBone = rootBone->getEndFixation()->addBone(local,btScalar(legRadius - legRadius*(i*.2)),btScalar(legLenght - legLenght*(i*.2)),btScalar(kneeRadius),lowerLimits,upperLimits);

        rootBone->getParentConstraint()->setAngularLowerLimit(btVector3(0,0,0));
        rootBone->getParentConstraint()->setAngularUpperLimit(btVector3(0,0,0));
    }
}

}
