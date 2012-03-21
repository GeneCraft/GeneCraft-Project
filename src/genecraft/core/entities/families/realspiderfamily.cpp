/*
Copyright 2012 Zéni David

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QDebug>
#include "realspiderfamily.h"
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
#include "sensors/contactsensor.h"

#include <ctime>

namespace GeneCraftCore {

RealSpiderFamily::RealSpiderFamily()
{
    sizeMultiplier = (btScalar)3.f;
    nbLegs      = 4;
    // Too much joints for the physics nbBoneInLeg = 7;
    nbBoneInLeg = 3;
    legRadius   = sizeMultiplier * (((btScalar)qrand())/RAND_MAX * 0.4 + 0.1);
    legLenght   = sizeMultiplier * (((btScalar)qrand())/RAND_MAX * 2 + 2.0);
    //kneeRadius  = ((btScalar)qrand())/RAND_MAX * 0.4 + 0.1;
    kneeRadius = sizeMultiplier*0.1;
    //headRadius  = ((btScalar)qrand())/RAND_MAX * 1. + legRadius*nbLegs/1.5 + 0.2;
    headRadius = sizeMultiplier*0.3;

    legSegmentLength = new btScalar*[nbLegs];
    legSegmentRadius = new btScalar*[nbLegs];

    anglesY = new btScalar*[nbLegs];

    for(int i = 0 ; i < nbLegs ; i++)
    {
        anglesY[i] = new btScalar[nbBoneInLeg];
        legSegmentLength[i] = new btScalar[nbBoneInLeg];
        legSegmentRadius[i] = new btScalar[nbBoneInLeg];
        for(int j = 0 ; j < nbBoneInLeg ; j++)
        {
            legSegmentRadius[i][j] = 0.1 * sizeMultiplier;
        }
    }

    lowerLimits = new btVector3[nbBoneInLeg];
    upperLimits = new btVector3[nbBoneInLeg];
    anglesZ = new btScalar[nbBoneInLeg];

    lowerLimits[0] = btVector3(-0.1,0,0);
    upperLimits[0] = btVector3(0.1,0,0);
    anglesY[0][0] = (btScalar)0.f;
    anglesY[1][0] = (btScalar)0.f;
    anglesY[2][0] = (btScalar)0.f;
    anglesY[3][0] = (btScalar)0.f;
    anglesZ[0] = SIMD_PI / 2.f;

    lowerLimits[1] = btVector3(0.0,0.0,-0.1f);
    upperLimits[1] = btVector3(0.0,0.0,SIMD_PI/12.f);
    anglesY[0][1] = (btScalar)0.f;
    anglesY[1][1] = (btScalar)0.f;
    anglesY[2][1] = (btScalar)0.f;
    anglesY[3][1] = (btScalar)0.f;
    anglesZ[1] = (btScalar)(-SIMD_PI*13.f/36.f);

    lowerLimits[2] = btVector3(0.0,0.0,-SIMD_PI/6.f);//SIMD_PI/12.f);
    upperLimits[2] = btVector3(0.0,0.0,0.01f);//0.0);
    anglesY[0][2] = (btScalar)-(SIMD_PI/16.f);
    anglesY[1][2] = (btScalar)-(SIMD_PI/12.f);
    anglesY[2][2] = (btScalar)(SIMD_PI/12.f);
    anglesY[3][2] = (btScalar)(SIMD_PI/16.f);
    anglesZ[2] = (btScalar)(SIMD_PI*23.f/36.f);

    /*** FRONT LEG ***/
    btScalar frontLegLength = 12.85875;//12.22375;
    legSegmentLength[0][0] = 0.91125 * legLenght / frontLegLength;
    legSegmentLength[0][1] = 3.92125 * legLenght / frontLegLength;
    legSegmentLength[0][2] = 6.82625 * legLenght / frontLegLength;
    /*** TOO MUCH JOINT FOR PHYSICS ***//*
    btScalar frontLegLength = 12.85875;//12.22375;
    legSegmentLength[0][0] = 0.740833333 * legLenght / frontLegLength;
    legSegmentLength[0][1] = 0.370416667 * legLenght / frontLegLength;
    legSegmentLength[0][2] = 3.65125 * legLenght / frontLegLength;
    legSegmentLength[0][3] = 1.27 * legLenght / frontLegLength;
    legSegmentLength[0][4] = 3.17500 * legLenght / frontLegLength;
    legSegmentLength[0][5] = 1.5875 * legLenght / frontLegLength;
    legSegmentLength[0][6] = 2.06375 * legLenght / frontLegLength;
    /*** END FRONT LEG ***/

    /*** MIDDLE FRONT LEG ***/
    btScalar middleFrontLegLength = 10.63625;//10.00125;
    legSegmentLength[1][0] = 1.01125 * legLenght / middleFrontLegLength;
    legSegmentLength[1][1] = 3.1275 * legLenght / middleFrontLegLength;
    legSegmentLength[1][2] = 5.3975 * legLenght / middleFrontLegLength;
    /*** TOO MUCH JOINT FOR PHYSICS ***//*
    btScalar middleFrontLegLength = 10.63625;//10.00125;
    legSegmentLength[1][0] = 0.740833333 * legLenght / middleFrontLegLength;
    legSegmentLength[1][1] = 0.370416667 * legLenght / middleFrontLegLength;
    legSegmentLength[1][2] = 2.8575 * legLenght / middleFrontLegLength;
    legSegmentLength[1][3] = 1.27 * legLenght / middleFrontLegLength;
    legSegmentLength[1][4] = 2.54 * legLenght / middleFrontLegLength;
    legSegmentLength[1][5] = 1.5875 * legLenght / middleFrontLegLength;
    legSegmentLength[1][6] = 1.27 * legLenght / middleFrontLegLength;
    /*** END MIDDLE FRONT LEG ***/

    /*** MIDDLE REAR LEG ***/
    btScalar middleRearLegLength = 9.2075;//8.41375;
    legSegmentLength[2][0] = 1.01125 * legLenght / middleRearLegLength;
    legSegmentLength[2][1] = 1.8575 * legLenght / middleRearLegLength;
    legSegmentLength[2][2] = 5.23875 * legLenght / middleRearLegLength;
    /*** TOO MUCH JOINT FOR PHYSICS ***//*
    btScalar middleRearLegLength = 9.2075;//8.41375;
    legSegmentLength[2][0] = 0.740833333 * legLenght / middleRearLegLength;
    legSegmentLength[2][1] = 0.370416667 * legLenght / middleRearLegLength;
    legSegmentLength[2][2] = 1.5875 * legLenght / middleRearLegLength;
    legSegmentLength[2][3] = 1.27 * legLenght / middleRearLegLength;
    legSegmentLength[2][4] = 2.38125 * legLenght / middleRearLegLength;
    legSegmentLength[2][5] = 1.5875 * legLenght / middleRearLegLength;
    legSegmentLength[2][6] = 1.27 * legLenght / middleRearLegLength;
    /*** END MIDDLE REAR LEG ***/

    /*** REAR LEG ***/
    btScalar rearLegLength = 11.1125;//10.16;
    legSegmentLength[3][0] = 1.01125 * legLenght / rearLegLength;
    legSegmentLength[3][1] = 2.81 * legLenght / rearLegLength;
    legSegmentLength[3][2] = 6.35 * legLenght / rearLegLength;
    /*** TOO MUCH JOINT FOR PHYSICS ***//*
    btScalar rearLegLength = 11.1125;//10.16;
    legSegmentLength[3][0] = 0.740833333 * legLenght / rearLegLength;
    legSegmentLength[3][1] = 0.370416667 * legLenght / rearLegLength;
    legSegmentLength[3][2] = 2.54 * legLenght / rearLegLength;
    legSegmentLength[3][3] = 1.11125 * legLenght / rearLegLength;
    legSegmentLength[3][4] = 2.8575 * legLenght / rearLegLength;
    legSegmentLength[3][5] = 1.90500 * legLenght / rearLegLength;
    legSegmentLength[3][6] = 1.5875 * legLenght / rearLegLength;
    /*** END REAR LEG ***/
}

RealSpiderFamily::~RealSpiderFamily()
{
    for(int i=0;i<nbLegs;i++)
    {
        delete legSegmentLength[i];
        delete legSegmentRadius[i];
        delete anglesY[i];
    }
    delete legSegmentLength;
    delete legSegmentRadius;
    delete lowerLimits;
    delete upperLimits;
    delete anglesY;
    delete anglesZ;

}

Entity* RealSpiderFamily::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {
    this->shapesFactory = shapesFactory;
    // root fixation
    Entity* ent = new Entity("Real Spider !", "RealSpiderFamily","real", 1);
    ent->setBrain(new BrainFunctional());
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(position);
    initTransform.getOrigin().setY(initTransform.getOrigin().getY()-5);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,btScalar(headRadius),initTransform);
    shape->setRoot(rootFix);
    ent->setShape(shape);
    //rootFix->addSensor(new GyroscopicSensor(rootFix));
    //rootFix->addSensor(new AccelerometerSensor(rootFix));

    // legs
    btQuaternion legLocal;
    btQuaternion legLocal2;
    for(int i=1;i<nbLegs+1;++i)
    {
        addLeg(1, i-1, rootFix,-i*((SIMD_PI)/(nbLegs+1)));
    }

    for(int i=1;i<nbLegs+1;++i)
    {
        addLeg(-1, i-1, rootFix,i*((SIMD_PI)/(nbLegs+1)));
    }

    // add rear body part
    rootFix->addBone(0, SIMD_PI*btScalar(0.5), 0.1 * sizeMultiplier, 0.05 * sizeMultiplier, btScalar(headRadius), btVector3(0,0,0), btVector3(0,0,0));

    return ent;
}

void RealSpiderFamily::addLeg(int rightSide, int legId,Fixation *fixBody, btScalar yAxis)
{
    Bone *rootBone = fixBody->addBone(yAxis, anglesZ[0],
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
    }
}

QVariant RealSpiderFamily::serialize() {
    return QVariant();
}

}

