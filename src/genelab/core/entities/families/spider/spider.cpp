#include <QDebug>
#include "spider.h"
#include "btshapesfactory.h"
#include "body/fixation.h"
#include "body/bone.h"
#include "body/treeshape.h"
#include "entity.h"
#include "LinearMath/btQuaternion.h"
#include "brain/brainfunctional.h"
#include "sensors/sensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/accelerometersensor.h"
#include "sensors/positionsensor.h"

#include <ctime>

namespace GeneLabCore {

Spider::Spider() :
    EntityFamily()
{
    nbLegs      = 4;
    nbBoneInLeg = 3;
    legRadius   = ((float)qrand())/RAND_MAX * 0.3 + 0.1;
    legLenght   = ((float)qrand())/RAND_MAX * 2 + 0.5;
    kneeRadius  = ((float)qrand())/RAND_MAX * 0.3 + 0.1;
    headRadius  = ((float)qrand())/RAND_MAX * 1 + legRadius*nbLegs/3;
}

Entity* Spider::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {
    this->shapesFactory = shapesFactory;
    this->initialPosition = position;
    // root fixation
    Entity* ent = new Entity("Spider !", "SpiderFamily", 1);
    ent->setBrain(new BrainFunctional(qrand()%25 + 1));
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(initialPosition);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,btScalar(headRadius),initTransform);
    shape->setRoot(rootFix);
    ent->setShape(shape);
    rootFix->addSensor(new GyroscopicSensor(rootFix));
    rootFix->addSensor(new AccelerometerSensor(1000/60., rootFix));
    // legs
    btQuaternion legLocal;
    btQuaternion legLocal2;
    btVector3 lowerLimits(0,0,0);
    btVector3 upperLimits(0,0,0);

    for(int i=1;i<nbLegs+1;++i)
    {
        addLeg(rootFix,-i*((M_PI)/(nbLegs+1)), M_PI / 3.0f,lowerLimits,upperLimits);
    }


    for(int i=1;i<nbLegs+1;++i)
    {
        addLeg(rootFix,i*((M_PI)/(nbLegs+1)), M_PI / 3.0f,lowerLimits,upperLimits);
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

    rootBone->getEndFixation()->addSensor(new GyroscopicSensor(rootBone->getEndFixation()));



    for(int i=1;i<nbBoneInLeg;++i)
    {
        btVector3 lowerLimits(0,0,-M_PI/10);
        btVector3 upperLimits(0,0,M_PI/6);
        float ang =  M_PI / 3.5f;
        rootBone = rootBone->getEndFixation()->addBone(0, ang,
                                                       btScalar(legRadius - legRadius*(i/nbBoneInLeg)),
                                                       btScalar(legLenght - legLenght*(i/nbBoneInLeg)),
                                                       btScalar(kneeRadius),
                                                       lowerLimits,
                                                       upperLimits);

        rootBone->getEndFixation()->addSensor(new AccelerometerSensor(1000/60., rootBone->getEndFixation()));

        //rootBone->getEndFixation()->addSensor(new PositionSensor(fixBody, rootBone->getEndFixation()));

        //rootBone->getParentConstraint()->setAngularLowerLimit(btVector3(0,0,0));
        //rootBone->getParentConstraint()->setAngularUpperLimit(btVector3(0,0,0));
    }
    {
        btVector3 lowerLimits(0,0,-M_PI/4);
        btVector3 upperLimits(0,0,0);
        rootBone->getEndFixation()->addBone(0,
                                            - M_PI / 3,
                                            btScalar(legRadius),
                                            btScalar(legLenght/2.),
                                            btScalar(kneeRadius/3.),
                                            lowerLimits,
                                            upperLimits);
    }
}

QVariant Spider::serialize() {
    return QVariant();
}

}
