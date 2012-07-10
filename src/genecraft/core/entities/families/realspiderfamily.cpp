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
#include "realspiderentity.h"
#include "LinearMath/btQuaternion.h"
#include "brain/brainfunctional.h"
#include "sensors/sensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/accelerometersensor.h"
#include "sensors/positionsensor.h"
#include "sensors/contactsensor.h"

#include <QDateTime>

namespace GeneCraftCore {

RealSpiderFamily::RealSpiderFamily()
{
    qsrand(QDateTime::currentDateTime ().toTime_t ());
    sizeMultiplier = (btScalar)3.f;
    nbLegs      = 4;
    // Too much joints for the physics nbBoneInLeg = 7;
    nbBoneInLeg = 4;
    legRadius   = sizeMultiplier * 0.09;//(((btScalar)qrand())/(btScalar)RAND_MAX * 0.02 + 0.08);
    legLenght   = sizeMultiplier * 3;//(((btScalar)qrand())/(btScalar)RAND_MAX * 2 + 2.0);
    //kneeRadius  = ((btScalar)qrand())/RAND_MAX * 0.4 + 0.1;
    kneeRadius = sizeMultiplier*0.1;
    //headRadius  = ((btScalar)qrand())/RAND_MAX * 1. + legRadius*nbLegs/1.5 + 0.2;
    headRadius = sizeMultiplier*0.25;

    legSegmentLength = new btScalar*[nbLegs];

    anglesY = new btScalar*[nbLegs];

    for(int i = 0 ; i < nbLegs ; i++)
    {
        anglesY[i] = new btScalar[nbBoneInLeg];
        legSegmentLength[i] = new btScalar[nbBoneInLeg];
    }

    lowerLimits = new btVector3[nbBoneInLeg];
    upperLimits = new btVector3[nbBoneInLeg];
    anglesZ = new btScalar[nbBoneInLeg];

    lowerLimits[0] = btVector3(-0.15,0,0);
    upperLimits[0] = btVector3(0.15,0,0);
    anglesY[0][0] = (btScalar)0.f;
    anglesY[1][0] = (btScalar)0.f;
    anglesY[2][0] = (btScalar)0.f;
    anglesY[3][0] = (btScalar)0.f;
    anglesZ[0] = SIMD_PI / 2.f;

    lowerLimits[1] = btVector3(0.0,0.0,-0.1f);
    upperLimits[1] = btVector3(0.0,0.0,SIMD_PI/12.f);
    anglesY[0][1] = (btScalar)-(SIMD_PI/64.f);
    anglesY[1][1] = (btScalar)-(SIMD_PI/48.f);
    anglesY[2][1] = (btScalar)(SIMD_PI/48.f);
    anglesY[3][1] = (btScalar)(SIMD_PI/64.f);
    anglesZ[1] = (btScalar)(-SIMD_PI*13.f/36.f);

    lowerLimits[2] = btVector3(0.0,0.0,-SIMD_PI/6.f);//SIMD_PI/12.f);
    upperLimits[2] = btVector3(0.0,0.0,SIMD_PI/30.f);//0.0);
    anglesY[0][2] = (btScalar)(SIMD_PI/8.f);
    anglesY[1][2] = (btScalar)(SIMD_PI/8.f);
    anglesY[2][2] = (btScalar)-(SIMD_PI/8.f);
    anglesY[3][2] = (btScalar)-(SIMD_PI/8.f);
    anglesZ[2] = (btScalar)(SIMD_PI/2.f);//23/36

    lowerLimits[3] = btVector3(0.0,0.0,-SIMD_PI/6.f);//SIMD_PI/12.f);
    upperLimits[3] = btVector3(0.0,0.0,SIMD_PI/6.f);//0.0);
    anglesY[0][3] = (btScalar)0.f;
    anglesY[1][3] = (btScalar)0.f;
    anglesY[2][3] = (btScalar)0.f;
    anglesY[3][3] = (btScalar)0.f;
    anglesZ[3] = (btScalar)(SIMD_PI/4.f);

    /*** FRONT LEG ***/
    initFrontLeg(legLenght);
    /*btScalar frontLegLength = 12.85875;//12.22375;
    legSegmentLength[0][0] = 0.91125 * legLenght / frontLegLength;
    legSegmentLength[0][1] = 3.92125 * legLenght / frontLegLength;
    legSegmentLength[0][2] = 3.41317 * legLenght / frontLegLength;
    legSegmentLength[0][3] = 3.41317 * legLenght / frontLegLength;*/
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
    initMiddleFrontLeg(legLenght);
    /*btScalar middleFrontLegLength = 10.63625;//10.00125;
    legSegmentLength[1][0] = 1.01125 * legLenght / middleFrontLegLength;
    legSegmentLength[1][1] = 3.1275 * legLenght / middleFrontLegLength;
    legSegmentLength[1][2] = 2.6987 * legLenght / middleFrontLegLength;
    legSegmentLength[1][3] = 2.6987 * legLenght / middleFrontLegLength;*/
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
    initMiddleRearLeg(legLenght);
    /*btScalar middleRearLegLength = 9.2075;//8.41375;
    legSegmentLength[2][0] = 1.01125 * legLenght / middleRearLegLength;
    legSegmentLength[2][1] = 1.8575 * legLenght / middleRearLegLength;
    legSegmentLength[2][2] = 2.6193 * legLenght / middleRearLegLength;
    legSegmentLength[2][3] = 2.6193 * legLenght / middleRearLegLength;*/
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
    initRearLeg(legLenght);
    /*btScalar rearLegLength = 11.1125;//10.16;
    legSegmentLength[3][0] = 1.01125 * legLenght / rearLegLength;
    legSegmentLength[3][1] = 2.81 * legLenght / rearLegLength;
    legSegmentLength[3][2] = 3.175 * legLenght / rearLegLength;
    legSegmentLength[3][3] = 3.175 * legLenght / rearLegLength;*/
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

void RealSpiderFamily::initFrontLeg(btScalar length)
{
    btScalar frontLegLength = 12.85875;//12.22375;
    legSegmentLength[0][0] = 0.91125 * length / frontLegLength;
    legSegmentLength[0][1] = 3.92125 * length / frontLegLength;
    legSegmentLength[0][2] = 3.41317 * length / frontLegLength;
    legSegmentLength[0][3] = 3.41317 * length / frontLegLength;
}

void RealSpiderFamily::initMiddleFrontLeg(btScalar length)
{
    btScalar middleFrontLegLength = 10.63625;//10.00125;
    legSegmentLength[1][0] = 1.01125 * length / middleFrontLegLength;
    legSegmentLength[1][1] = 3.1275 * length / middleFrontLegLength;
    legSegmentLength[1][2] = 2.6987 * length / middleFrontLegLength;
    legSegmentLength[1][3] = 2.6987 * length / middleFrontLegLength;
}

void RealSpiderFamily::initMiddleRearLeg(btScalar length)
{
    btScalar middleRearLegLength = 9.2075;//8.41375;
    legSegmentLength[2][0] = 1.01125 * length / middleRearLegLength;
    legSegmentLength[2][1] = 1.8575 * length / middleRearLegLength;
    legSegmentLength[2][2] = 2.6193 * length / middleRearLegLength;
    legSegmentLength[2][3] = 2.6193 * length / middleRearLegLength;
}

void RealSpiderFamily::initRearLeg(btScalar length)
{
    btScalar rearLegLength = 11.1125;//10.16;
    legSegmentLength[3][0] = 1.01125 * length / rearLegLength;
    legSegmentLength[3][1] = 2.81 * length / rearLegLength;
    legSegmentLength[3][2] = 3.175 * length / rearLegLength;
    legSegmentLength[3][3] = 3.175 * length / rearLegLength;
}

RealSpiderFamily::~RealSpiderFamily()
{
    for(int i=0;i<nbLegs;i++)
    {
        delete legSegmentLength[i];
        delete anglesY[i];
    }
    delete legSegmentLength;
    delete lowerLimits;
    delete upperLimits;
    delete anglesY;
    delete anglesZ;

}

void RealSpiderFamily::initRealSpider()
{

}

Entity* RealSpiderFamily::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {

    this->shapesFactory = shapesFactory;
    // root fixation
    RealSpiderEntity* ent = new RealSpiderEntity("Real Spider !", "RealSpiderFamily","generic", 1);
    ent->setBrain(new BrainFunctional());

    QVariantMap params;
    params.insert("headRadius", QVariant((double)headRadius));
    params.insert("kneeRadius", QVariant((double)kneeRadius));
    params.insert("legRadius", QVariant((double)legRadius));

    QVariantMap lengths;
    lengths.insert("front", QVariant((double)legLenght));
    lengths.insert("middleFront", QVariant((double)legLenght));
    lengths.insert("middleRear", QVariant((double)legLenght));
    lengths.insert("rear", QVariant((double)legLenght));

    params.insert("legLength", lengths);
    ent->setParams(params);

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

    // Create and add left legs
    for(int i=1;i<nbLegs+1;++i)
    {
        anglesY[nbLegs-i][0] = -i*((SIMD_PI)/(nbLegs+1));
        ent->addLeftLeg(Leg::createLeftLeg(i, nbBoneInLeg, rootFix, anglesY[nbLegs-i], anglesZ, kneeRadius, lowerLimits, upperLimits, legRadius, legSegmentLength[nbLegs-i]));
    }

    // Create and add right legs
    for(int i=1;i<nbLegs+1;++i)
    {
        anglesY[nbLegs-i][0] = i*((SIMD_PI)/(nbLegs+1));
        ent->addRightLeg(Leg::createRightLeg(i, nbBoneInLeg, rootFix, anglesY[nbLegs-i], anglesZ, kneeRadius, lowerLimits, upperLimits, legRadius, legSegmentLength[nbLegs-i]));
    }

    // add rear body part
    rootFix->addBone(0, SIMD_PI*btScalar(0.5), 0.1 * sizeMultiplier, 0.05 * sizeMultiplier, btScalar(headRadius), btVector3(0,0,0), btVector3(0,0,0));

    return ent;
}

Entity* RealSpiderFamily::createEntity(QVariant genotype, btShapesFactory *shapesFactory, const btVector3 &position) {

    QVariantMap entityMap = genotype.toMap();

    // Entity & origins
    QVariantMap origins = entityMap.value("origins").toMap();
    RealSpiderEntity * ent = new RealSpiderEntity(origins.value("name").toString(),
                                                  origins.value("family").toString(),
                                                  "generic",
                                                  origins.value("generation").toInt());

    this->shapesFactory = shapesFactory;

    ent->setBrain(new BrainFunctional(entityMap.value("brain")));

    QVariantMap parameters = entityMap.value("params").toMap();
    ent->setParams(parameters);
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(position);
    initTransform.getOrigin().setY(initTransform.getOrigin().getY()-5);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,btScalar(parameters.value("headRadius").toFloat()),initTransform);
    shape->setRoot(rootFix);
    ent->setShape(shape);
    //rootFix->addSensor(new GyroscopicSensor(rootFix));
    //rootFix->addSensor(new AccelerometerSensor(rootFix));

    QVariantMap lengths = parameters.value("legLength").toMap();
    initFrontLeg(lengths.value("front").toFloat());
    initMiddleFrontLeg(lengths.value("middleFront").toFloat());
    initMiddleRearLeg(lengths.value("middleRear").toFloat());
    initRearLeg(lengths.value("rear").toFloat());

    // legs
    btQuaternion legLocal;
    btQuaternion legLocal2;

    foreach(QVariant effect, entityMap.value("body").toMap().value("shape").toMap().value("rootFix").toMap()["effectors"].toList())
    {
        QVariantMap effectorMap = effect.toMap();
        if((EffectorType)effectorMap["type"].toInt() == legEffector)
        {
            QVariantMap leg = effectorMap.value("leg").toMap();

            int i = leg.value("number").toInt();
            if(leg.value("side").toInt()>0)
            {
                anglesY[nbLegs-i][0] = i*((SIMD_PI)/(nbLegs+1));
                ent->addRightLeg(Leg::createRightLeg(effectorMap, i, nbBoneInLeg, rootFix, anglesY[nbLegs-i], anglesZ, btScalar(parameters.value("kneeRadius").toFloat()), lowerLimits, upperLimits, btScalar(parameters.value("legRadius").toFloat()), legSegmentLength[nbLegs-i]));
            }
            else
            {
                anglesY[nbLegs-i][0] = -i*((SIMD_PI)/(nbLegs+1));
                ent->addLeftLeg(Leg::createLeftLeg(effectorMap, i, nbBoneInLeg, rootFix, anglesY[nbLegs-i], anglesZ, btScalar(parameters.value("kneeRadius").toFloat()), lowerLimits, upperLimits, btScalar(parameters.value("legRadius").toFloat()), legSegmentLength[nbLegs-i]));
            }
        }
    }

    // add rear body part
    rootFix->addBone(0, SIMD_PI*btScalar(0.5), 0.1 * sizeMultiplier, 0.05 * sizeMultiplier, btScalar(parameters.value("headRadius").toFloat()), btVector3(0,0,0), btVector3(0,0,0));

    return ent;
}

QVariant RealSpiderFamily::serialize(Entity *entity)
{
    QVariantMap genome;
    genome = entity->serialize().toMap();
    genome.insert("params", ((RealSpiderEntity*) entity)->getParams());
    return genome;
}

}

