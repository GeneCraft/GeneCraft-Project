#include "spider.h"
#include "btshapesfactory.h"
#include "fixation.h"
#include "bone.h"
#include "treeshape.h"
#include "entity.h"
#include "LinearMath/btQuaternion.h"

namespace GeneLabCore {

Spider::Spider() :
    EntityFamily()
{
    nbLegs      = 8;
    nbBoneInLeg = 4;
    legRadius   = 0.1;
    legLenght   = 8;
    kneeRadius  = 0.35;

}

Entity* Spider::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {
    this->shapesFactory = shapesFactory;
    this->initialPosition = position;
    // root fixation
    Entity* ent = new Entity("Spider !", "SpiderFamily", 1);
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(initialPosition);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,btScalar(1),initTransform);
    shape->setRoot(rootFix);
    ent->setShape(shape);
    // legs
    btQuaternion legLocal;
    legLocal.setEulerZYX(0,0,0);
    btVector3 lowerLimits(0,0,0);
    btVector3 upperLimits(0,0,0);

    for(int i=0;i<nbLegs;++i)
    {
        legLocal.setEulerZYX(M_PI/2.0,0,i*(2.0*M_PI/nbLegs));
        addLeg(rootFix,legLocal,lowerLimits,upperLimits);
    }

    return ent;
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

QVariant Spider::serialize() {
    return QVariant();
}

}
