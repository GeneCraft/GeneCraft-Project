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

#include <QDebug>
#include "spiderfamily.h"
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

SpiderFamily::SpiderFamily() :
    EntityFamily()
{
    nbLegs      = 4;
    nbBoneInLeg = 3;
    legRadius   = ((btScalar)qrand())/RAND_MAX * 0.4 + 0.1;
    legLenght   = ((btScalar)qrand())/RAND_MAX * 2 + 0.5;
    kneeRadius  = ((btScalar)qrand())/RAND_MAX * 0.4 + 0.1;
    headRadius  = ((btScalar)qrand())/RAND_MAX * 1. + legRadius*nbLegs/1.5 + 0.2;
}

Entity* SpiderFamily::createEntity(btShapesFactory *shapesFactory, const btVector3 &position) {
    this->shapesFactory = shapesFactory;
    // root fixation
    Entity* ent = new Entity("Spider !", "SpiderFamily","generic", 1);
    ent->setBrain(new BrainFunctional());
    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(position);
    TreeShape* shape = new TreeShape(shapesFactory);
    Fixation* rootFix = new Fixation(shapesFactory,btScalar(headRadius),initTransform);
    shape->setRoot(rootFix);
    ent->setShape(shape);
    //rootFix->addSensor(new GyroscopicSensor(rootFix));
    //rootFix->addSensor(new AccelerometerSensor(rootFix));
    // legs
    btQuaternion legLocal;
    btQuaternion legLocal2;
    btVector3 lowerLimits(-0.1,0,0);
    btVector3 upperLimits(0.1,0,0.7);

    for(int i=1;i<nbLegs+1;++i)
    {
        addLeg(rootFix,-i*((SIMD_PI)/(nbLegs+1)), SIMD_PI / 2.f,lowerLimits,upperLimits);
    }


    for(int i=1;i<nbLegs+1;++i)
    {
        addLeg(rootFix,i*((SIMD_PI)/(nbLegs+1)), SIMD_PI / 2.f,lowerLimits,upperLimits);
    }

    return ent;
}

void SpiderFamily::addLeg(Fixation *fixBody, btScalar yAxis, btScalar zAxis, const btVector3 &lowerLimits, const btVector3 &upperLimits)
{
    Bone *rootBone = fixBody->addBone(yAxis, zAxis,
                                      btScalar(legRadius),
                                      btScalar(legLenght),
                                      btScalar(kneeRadius),
                                      lowerLimits,upperLimits);

    //rootBone->getEndFixation()->addSensor(new GyroscopicSensor(rootBone->getEndFixation()));



    for(int i=1;i<nbBoneInLeg;++i)
    {
        btVector3 lowerLimits(0,0,-SIMD_PI/10.);
        btVector3 upperLimits(0,0,SIMD_PI/10.);
        btScalar ang =  SIMD_PI / 12.f;
        rootBone = rootBone->getEndFixation()->addBone(0, ang,
                                                       btScalar(legRadius - legRadius*(i/nbBoneInLeg)),
                                                       btScalar(legLenght - legLenght*(i/nbBoneInLeg)),
                                                       btScalar(kneeRadius),
                                                       lowerLimits,
                                                       upperLimits);

        //rootBone->getEndFixation()->addSensor(new AccelerometerSensor(rootBone->getEndFixation()));

        //rootBone->getEndFixation()->addSensor(new PositionSensor(fixBody, rootBone->getEndFixation()));

        //rootBone->getParentConstraint()->setAngularLowerLimit(btVector3(0,0,0));
        //rootBone->getParentConstraint()->setAngularUpperLimit(btVector3(0,0,0));
    }
    {
        btVector3 lowerLimits(0,0,-SIMD_PI/4.);
        btVector3 upperLimits(0,0,0);
        rootBone->getEndFixation()->addBone(0,
                                            - SIMD_PI / 4.,
                                            btScalar(legRadius),
                                            btScalar(legLenght/2.),
                                            btScalar(kneeRadius/3.),
                                            lowerLimits,
                                            upperLimits);
        //lastBone->getEndFixation()->addSensor(new ContactSensor(lastBone->getEndFixation()));
    }
}

QVariant SpiderFamily::serialize() {
    return QVariant();
}

}
