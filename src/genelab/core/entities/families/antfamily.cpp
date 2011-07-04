#include "antfamily.h"

#include "btshapesfactory.h"
#include "body/fixation.h"
#include "body/bone.h"
#include "body/treeshape.h"
#include "entity.h"
#include "LinearMath/btQuaternion.h"
#include "sensors/sensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/accelerometersensor.h"
#include "sensors/positionsensor.h"
#include "tools.h"

namespace GeneLabCore {

AntFamily::AntFamily() : EntityFamily()
{
    // head / trunk / metasoma
    headRadius      = Tools::random(0.5,1.2);
    trunkRadius     = Tools::random(0.8,1.2);
    metasomaRadius  = Tools::random(headRadius,headRadius+1.0);

    // legs
    nbBonesInLeg    = Tools::random(2,3);
    legRadius       = Tools::random(0.1,0.3);
    legLenght       = Tools::random(0.1,2.0);
    kneeRadius      = Tools::random(0.1,0.5);
}

Entity* AntFamily::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {
    this->shapesFactory = shapesFactory;

    Entity* ent = new Entity("Ant", "AntFamily", 1);
    ent->setBrain(new BrainFunctional(Brain::randomPlugGridSize()));

    // root fixation
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(position);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,headRadius,initTransform);
    shape->setRoot(rootFix);
    ent->setShape(shape);
    rootFix->addSensor(new GyroscopicSensor(rootFix));

    // legs
    btQuaternion legLocal;
    legLocal.setEulerZYX(0,0,0);
    btVector3 lowerLimits(0,0,0);
    btVector3 upperLimits(0,0,0);

    btQuaternion local;

    local.setEulerZYX(M_PI/2.0,0,0);
    Bone * bone = rootFix->addBone(0, M_PI/2.0f, 0.5, 0.5, trunkRadius, lowerLimits, upperLimits);

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
    bone = bone->getEndFixation()->addBone(0,0,0.5,0.5,metasomaRadius,lowerLimits,upperLimits);

    return ent;
}

void AntFamily::addLeg(Fixation *fixBody, btScalar yAxis, btScalar zAxis, const btVector3 &lowerLimits, const btVector3 &upperLimits)
{
    Bone *rootBone = fixBody->addBone(yAxis, zAxis,
                                      btScalar(legRadius),
                                      btScalar(legLenght),
                                      btScalar(kneeRadius),
                                      lowerLimits,upperLimits);

    rootBone->getEndFixation()->addSensor(new AccelerometerSensor(rootBone->getEndFixation()));

    for(int i=1;i<nbBonesInLeg;++i)
    {
        btVector3 lowerLimits(0,0,-M_PI/4);
        btVector3 upperLimits(M_PI / 12,0,M_PI/4);
        btQuaternion local;
        local.setEulerZYX(M_PI/6.0,0,0);

        rootBone = rootBone->getEndFixation()->addBone(-yAxis, M_PI / 6,
                                                       btScalar(legRadius - legRadius*(i/nbBonesInLeg)),
                                                       btScalar(legLenght - legLenght*(i/nbBonesInLeg)),
                                                       btScalar(kneeRadius),
                                                       lowerLimits,
                                                       upperLimits);

        rootBone->getEndFixation()->addSensor(new PositionSensor(fixBody, rootBone->getEndFixation()));
        rootBone->getEndFixation()->addSensor(new AccelerometerSensor(rootBone->getEndFixation()));
        yAxis = 0;
    }
}

QVariant AntFamily::serialize() {
    return QVariant(); // TODO
}
}
