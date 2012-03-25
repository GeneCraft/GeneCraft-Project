#include "leg.h"

#include "body/fixation.h"
#include "body/bone.h"

namespace GeneCraftCore {

Leg::Leg(int rightSide, int legId,Fixation *fixBody, btScalar yAxis)
{
    /*Bone *rootBone = fixBody->addBone(yAxis, anglesZ[0],
                                      btScalar(legSegmentRadius[nbLegs-legId-1][0]),
                                      btScalar(legSegmentLength[nbLegs-legId-1][0]),
                                      btScalar(kneeRadius),
                                      lowerLimits[0],
                                      upperLimits[0]);

    for(int i=1;i<nbBoneInLeg;++i)
    {
        rootBone = rootBone->getEndFixation()->addBone(rightSide*anglesY[nbLegs-legId-1][i], anglesZ[i],
                                                       btScalar(legSegmentRadius[nbLegs-legId-1][i]),
                                                       btScalar(legSegmentLength[nbLegs-legId-1][i]),
                                                       btScalar(kneeRadius),
                                                       lowerLimits[i],
                                                       upperLimits[i]);

        //rootBone->getEndFixation()->addSensor(new AccelerometerSensor(rootBone->getEndFixation()));

        //rootBone->getEndFixation()->addSensor(new PositionSensor(fixBody, rootBone->getEndFixation()));

        //rootBone->getParentConstraint()->setAngularLowerLimit(btVector3(0,0,0));
        //rootBone->getParentConstraint()->setAngularUpperLimit(btVector3(0,0,0));
    }*/
}

}
