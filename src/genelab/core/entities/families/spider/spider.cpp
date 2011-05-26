#include "spider.h"
#include "btshapesfactory.h"
#include "fixation.h"
#include "bone.h"

namespace GeneLabCore {

Spider::Spider(btShapesFactory *shapesFactory, const btVector3 &position) :
    Entity("Spider","SpiderFamily",1), shapesFactory(shapesFactory), initialPosition(position)
{
    nbLegs      = 8;
    nbBoneInLeg = 2;
    legRadius   = 0.3;
    legLenght   = 2;
    kneeRadius  = 0.35;

    // root fixation
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(initialPosition);
    rootFix = new Fixation(shapesFactory,btScalar(1),initTransform);
    rootFix->setEntity(this);

    // legs
    btQuaternion legLocal;
    btVector3 lowerLimits(0,0,0);
    btVector3 upperLimits(0,0,0);

    for(int i=0;i<nbLegs;++i)
    {
        legLocal.setEulerZYX(M_PI/2.0,0,i*(2.0*M_PI/nbLegs));
        addLeg(rootFix,legLocal,lowerLimits,upperLimits);
    }
}

void Spider::addLeg(Fixation *fixBody, const btQuaternion &localFix, const btVector3 &lowerLimits, const btVector3 &upperLimits)
{
    Bone *rootBone = fixBody->addBone(localFix,
                                      btScalar(legRadius),
                                      btScalar(legLenght),
                                      btScalar(kneeRadius),
                                      lowerLimits,upperLimits);

    for(int i=1;i<nbBoneInLeg;++i)
    {
        btQuaternion local;

        local.setEulerZYX(M_PI/3.0,0,0);
        rootBone = rootBone->getEndFixation()->addBone(local,
                                                       btScalar(legRadius - legRadius*(i*.2)),
                                                       btScalar(legLenght - legLenght*(i*.2)),
                                                       btScalar(kneeRadius),
                                                       lowerLimits,
                                                       upperLimits);

        //rootBone->getParentConstraint()->setAngularLowerLimit(btVector3(0,0,0));
        //rootBone->getParentConstraint()->setAngularUpperLimit(btVector3(0,0,0));
    }
}

}
