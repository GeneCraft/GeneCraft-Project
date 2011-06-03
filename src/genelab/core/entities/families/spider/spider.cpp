#include <QDebug>
#include "spider.h"
#include "btshapesfactory.h"
#include "fixation.h"
#include "bone.h"
#include "treeshape.h"
#include "entity.h"
#include "LinearMath/btQuaternion.h"
#include "brainfunctional.h"
#include "sensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/accelerometersensor.h"
#include "sensors/positionsensor.h"

namespace GeneLabCore {

Spider::Spider() :
    EntityFamily()
{
    nbLegs      = 8;
    nbBoneInLeg = 3;
    legRadius   = 0.3;
    legLenght   = 3.0;
    kneeRadius  = 0.25;
}

Entity* Spider::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {
    this->shapesFactory = shapesFactory;
    this->initialPosition = position;
    // root fixation
    Entity* ent = new Entity("Spider !", "SpiderFamily", 1);
    ent->setBrain(new BrainFunctional(25));
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(initialPosition);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,btScalar(1),initTransform);
    rootFix->addSensor(new GyroscopicSensor(rootFix));
    shape->setRoot(rootFix);
    ent->setShape(shape);
    // legs
    btQuaternion legLocal;
    btQuaternion legLocal2;
    btVector3 lowerLimits(0,0,0);
    btVector3 upperLimits(0,0,0);

    for(int i=0;i<nbLegs;++i)
    {
        legLocal.setRotation(btVector3(0, 0, 1), M_PI / 3.0);
        legLocal2.setRotation(btVector3(0, 1, 0), i*(2.0*M_PI/nbLegs));
        legLocal2 *= legLocal;
        //legLocal = legLocal2;
        addLeg(rootFix,i*(2.0*M_PI/nbLegs), M_PI / 3.0f,lowerLimits,upperLimits);
    }

    return ent;
}

void Spider::addLeg(Fixation *fixBody, btScalar yAxis, btScalar zAxis, const btVector3 &lowerLimits, const btVector3 &upperLimits)
{
    Bone *rootBone = fixBody->addBone(yAxis, zAxis,
                                      btScalar(legRadius),
                                      btScalar(legLenght),
                                      btScalar(kneeRadius),
                                      lowerLimits,upperLimits);

    rootBone->getEndFixation()->addSensor(new PositionSensor(fixBody, rootBone->getEndFixation()));



    for(int i=1;i<nbBoneInLeg;++i)
    {
        btVector3 lowerLimits(0,0,-M_PI/10);
        btVector3 upperLimits(0,0,M_PI/6);
        rootBone = rootBone->getEndFixation()->addBone(0, M_PI / 3.5f,
                                                       btScalar(legRadius - legRadius*(i/nbBoneInLeg)),
                                                       btScalar(legLenght - legLenght*(i/nbBoneInLeg)),
                                                       btScalar(kneeRadius),
                                                       lowerLimits,
                                                       upperLimits);

        rootBone->getEndFixation()->addSensor(new GyroscopicSensor(rootBone->getEndFixation()));
        rootBone->getEndFixation()->addSensor(new AccelerometerSensor(1000/60., rootBone->getEndFixation()));

        //rootBone->getParentConstraint()->setAngularLowerLimit(btVector3(0,0,0));
        //rootBone->getParentConstraint()->setAngularUpperLimit(btVector3(0,0,0));
    }
}

QVariant Spider::serialize() {
    return QVariant();
}

}
