/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

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

namespace GeneCraftCore {

AntFamily::AntFamily() : EntityFamily()
{
    // head / trunk / metasoma
    headRadius      = Tools::random(0.5,1.2);
    trunkRadius     = Tools::random(0.8,1.2);
    metasomaRadius  = Tools::random((double)headRadius, (double)headRadius+1.0);

    // legs
    nbBonesInLeg    = Tools::random(2,3);
    legRadius       = Tools::random(0.1,0.3);
    legLenght       = Tools::random(0.1,2.0);
    kneeRadius      = Tools::random(0.1,0.5);
}

Entity* AntFamily::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {
    this->shapesFactory = shapesFactory;

    Entity* ent = new Entity("Ant", "AntFamily", "generic", 1);
    ent->setBrain(new BrainFunctional());

    // root fixation
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(position);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,headRadius,initTransform);
    shape->setRoot(rootFix);
    ent->setShape(shape);
    //rootFix->addSensor(new GyroscopicSensor(rootFix));

    // legs
    btQuaternion legLocal;
    legLocal.setEulerZYX(0,0,0);
    btVector3 lowerLimits(0,0,0);
    btVector3 upperLimits(0,0,0);

    btQuaternion local;

    local.setEulerZYX(SIMD_PI/2.0,0,0);
    Bone * bone = rootFix->addBone(0, SIMD_PI/2.0f, 0.5, 0.5, trunkRadius, lowerLimits, upperLimits);

    for(int i=0;i<3;++i)
    {
        legLocal.setEulerZYX(0,0, SIMD_PI / 6.0f * i + SIMD_PI / 3.0);
        addLeg(bone->getEndFixation(),SIMD_PI / 2.0f, SIMD_PI / 6.0f * i + SIMD_PI / 3.0,lowerLimits,upperLimits);
    }

    for(int i=0;i<3;++i)
    {
        legLocal.setEulerZYX(0,0, - SIMD_PI / 6.0f * i - SIMD_PI / 3.0);
        addLeg(bone->getEndFixation(),SIMD_PI / 2.0, -SIMD_PI / 6.0f * i - SIMD_PI / 3.0,lowerLimits,upperLimits);
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

    //rootBone->getEndFixation()->addSensor(new AccelerometerSensor(rootBone->getEndFixation()));

    for(int i=1;i<nbBonesInLeg;++i)
    {
        btVector3 lowerLimits(0,0,-SIMD_PI/4);
        btVector3 upperLimits(SIMD_PI / 12,0,SIMD_PI/4);
        btQuaternion local;
        local.setEulerZYX(SIMD_PI/6.0,0,0);

        rootBone = rootBone->getEndFixation()->addBone(-yAxis, SIMD_PI / 6,
                                                       btScalar(legRadius - legRadius*(i/nbBonesInLeg)),
                                                       btScalar(legLenght - legLenght*(i/nbBonesInLeg)),
                                                       btScalar(kneeRadius),
                                                       lowerLimits,
                                                       upperLimits);

        //rootBone->getEndFixation()->addSensor(new PositionSensor(fixBody, rootBone->getEndFixation()));
        //rootBone->getEndFixation()->addSensor(new AccelerometerSensor(rootBone->getEndFixation()));
        yAxis = 0;
    }
}

QJsonObject AntFamily::serialize() {
    return QJsonObject(); // TODO
}
}
