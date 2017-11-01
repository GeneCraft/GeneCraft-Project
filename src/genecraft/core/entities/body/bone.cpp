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

#include "bone.h"

// Qt
#include <QTest>

// Entity
#include "entity.h"
#include "body/fixation.h"
#include "effectors/rotationalmotorseffector.h"

// Engine
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "bullet/rigidbodyorigin.h"
#include "bullet/bulletengine.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "BulletCollision/CollisionShapes/btCompoundShape.h"
#include "bullet/shapes/btcylinder.h"
#include "bullet/shapes/btbone.h"
#include "btshapesfactory.h"

// Others
#include "tools.h"

// World
#include "bullet/btworld.h"
#include <QJsonArray>


namespace GeneCraftCore {

Bone::Bone(btShapesFactory *shapesFactory, btScalar yAxis, btScalar zAxis, btScalar radius, btScalar length, btScalar endFixRadius, const btTransform &initTransform)
    : QObject(), yAxis(yAxis), zAxis(zAxis), parentFix(NULL), motorsEffector(NULL)
{

    motorModifierData = QJsonObject();
    parentCt = 0;
    body         = shapesFactory->createBone(length, radius, endFixRadius, initTransform);
    rigidBody    = body->getRigidBody();

    btVector3 position(btScalar(0), length*0.5 + endFixRadius, btScalar(0));
    btTransform endTransform;
    endTransform.setIdentity();
    endTransform.setOrigin(position);

    endFix      = new Fixation(shapesFactory, rigidBody, endFixRadius, endTransform, this);

    this->shapesFactory = shapesFactory;
}

Bone::~Bone()
{
    delete motorsEffector;
    shapesFactory->getWorld()->getBulletWorld()->removeConstraint(parentCt);
    delete parentCt;
    delete endFix;
    delete origin;
    delete body;
}

void Bone::remove() {

//    do it out of here, else bones are remove from fix and can't be deleted because we lose the pointer...
//    if(parentFix != NULL) {
//        parentFix->removeBone(this);
//        parentFix = NULL;
//    }

    endFix->remove();
    entity->removeLinksToEffector(this->motorsEffector);
    disconnectMotor(0);
    disconnectMotor(1);
    disconnectMotor(2);
}

void Bone::removeOnly()
{
    if(parentFix != NULL) {
        endFix->removeAndAttachChildrenTo(parentFix);
        entity->removeLinksToEffector(this->motorsEffector);
        disconnectMotor(0);
        disconnectMotor(1);
        disconnectMotor(2);
    }
}

void Bone::setup()
{
    // shape
    body->setup();

    // origins
    origin = new RigidBodyOrigin(RigidBodyOrigin::BONE,(QObject *)this);
    rigidBody->setUserPointer(origin);

    // parent constraint
    if(parentCt)
    {
        // state
        rigidBody->setActivationState(DISABLE_DEACTIVATION);
        for(int i=0;i<3;i++)
        {
            btRotationalLimitMotor * motor = parentCt->getRotationalLimitMotor(i);
            motor->m_enableMotor = true;

            motor->m_limitSoftness = 0.0f;
            motor->m_normalCFM = 0.0;
            motor->m_stopERP = 0.2f; // Error tolerance factor when joint is at limit.
            motor->m_stopCFM = 0.0f ; // Constraint force mixing factor when joint is at limit.
            motor->m_maxMotorForce = 0.001f;
            motor->m_maxLimitForce = 0.001f;
            motor->m_targetVelocity = 0;
            motor->m_bounce = 0.0;
            motor->m_damping = 0.5;
        }


        // add motor modifier
        if(motorModifierData != QJsonObject()) {
            QJsonObject motor = motorModifierData;
            if(!motor.contains("typename")) {
                motor.insert("typename", "Rotational Motor");
                motor.insert("type", (int)rotationalMotorEffector);
            }

            motorsEffector = new RotationalMotorsEffector(motorModifierData, this, parentCt);
        }
        else
            motorsEffector = new RotationalMotorsEffector(this, parentCt);

        if(entity)
           entity->addLinkToEffector(motorsEffector);

        // attach to its parent
        shapesFactory->getWorld()->getBulletWorld()->addConstraint(parentCt, true);
    }

    //bulletEngine->getBulletDynamicsWorld()->addConstraint(endFixConstraint, true);
    endFix->setup();
}

void Bone::setEntity(Entity *entity)
{
    this->entity = entity;

    endFix->setEntity(entity);
}

// ------------
// -- MOTORS --
// ------------

void Bone::disableMotors()
{
    motorsEffector->disable();
}

void Bone::setBrainMotors()
{
    motorsEffector->setOutputsFrom(1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/);
}

void Bone::setNormalPositionMotors()
{
    motorsEffector->setOutputsFrom(0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/);
}

void Bone::setRandomMotors()
{
    motorsEffector->setOutputsFrom(2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/);
}

void Bone::resetMotors()
{
    // Angular Limit Motors
    btRotationalLimitMotor *motor;
    for(int i=0;i<3;i++)
    {
        motor = parentCt->getRotationalLimitMotor(i);

        motor->m_enableMotor    = true;
        motor->m_targetVelocity = btScalar(0);
        motor->m_maxMotorForce  = btScalar(1000);
        motor->m_maxLimitForce  = btScalar(300);
        motor->m_loLimit        = btScalar(0); // TODO initial value
        motor->m_hiLimit        = btScalar(0); // TODO initial value
    }
}

void Bone::disconnectMotor(int i)
{
    if(entity && motorsEffector->getBrainOutputs(i))
    {
        entity->removeBrainOut(motorsEffector->getBrainOutputs(i)->boMaxMotorForce);
        entity->removeBrainOut(motorsEffector->getBrainOutputs(i)->boTargetVelocity);

        motorsEffector->disconnectMotor(i);
    }
}

void Bone::connectMotor(int i)
{
    if(entity && motorsEffector)
    {
        motorsEffector->connectMotor(i);

        if(motorsEffector->getBrainOutputs(i)) {
            entity->addBrainOut(motorsEffector->getBrainOutputs(i)->boMaxMotorForce);
            entity->addBrainOut(motorsEffector->getBrainOutputs(i)->boTargetVelocity);
        }
    }
}

// ----------------------
// -- INITIAL POSITION --
// ----------------------

void Bone::setyAxis(btScalar yAxis) {
    this->yAxis = yAxis;
    btQuaternion local1;
    local1.setRotation(btVector3(0, 1, 0), yAxis);
    btQuaternion local2;
    local2.setRotation(btVector3(0, 0, 1), zAxis);
    local1 *= local2;

    parentCt->getFrameOffsetA().setRotation(local1);
}

void Bone::setZAxis(btScalar zAxis) {
    this->zAxis = zAxis;
    btQuaternion local1;
    local1.setRotation(btVector3(0, 1, 0), yAxis);
    btQuaternion local2;
    local2.setRotation(btVector3(0, 0, 1), zAxis);
    local1 *= local2;

    parentCt->getFrameOffsetA().setRotation(local1);
}

// -------------------
// -- SERIALIZATION --
// -------------------

QJsonObject Bone::serialize()
{
    QJsonObject bone;

    // Length & radius
    bone.insert("length",(double)getLength());
    bone.insert("radius",(double)getRadius());

    // Yaw & Roll
    QJsonObject localRotation;
    localRotation.insert("y",(double)getYAxis());
    localRotation.insert("z",(double)getZAxis());
    bone.insert("localRotation",localRotation);

    // Limits
    QJsonObject lowerlimits, upperlimits;
    btVector3 angularLowerLimits, angularUpperLimits;
    parentCt->getAngularLowerLimit(angularLowerLimits);
    parentCt->getAngularUpperLimit(angularUpperLimits);

    lowerlimits.insert("x",(double)angularLowerLimits.x());
    lowerlimits.insert("y",(angularLowerLimits.y()));
    lowerlimits.insert("z",(double)angularLowerLimits.z());

    upperlimits.insert("x",(double)angularUpperLimits.x());
    upperlimits.insert("y",(double)angularUpperLimits.y());
    upperlimits.insert("z",(double)angularUpperLimits.z());

    bone.insert("lowerLimits",lowerlimits);
    bone.insert("upperLimits",upperlimits);

    // End fixation
    bone.insert("endFix",endFix->serialize());

    if(motorsEffector) // FIXME you can't serialize motorsEffector if entity isn't still setup !
        bone.insert("muscle", this->motorsEffector->serialize());

    return bone;
}

QJsonObject Bone::generateEmpty() {

    QJsonObject bone;

    // TODO right values ???
    // Length & radius
    bone.insert("length",(double)Tools::random(0.5,3.0));
    bone.insert("radius",(double)Tools::random(0.1,0.5));

    // Yaw & Roll
    QJsonObject localRotation;
    localRotation.insert("y",(double)Tools::random(-SIMD_PI,SIMD_PI));
    localRotation.insert("z",(double)Tools::random(-SIMD_PI,SIMD_PI));
    bone.insert("localRotation",localRotation);

    // Limits
    QJsonObject lowerlimits, upperlimits;

    btScalar lowerLimit_x = Tools::random(-SIMD_PI/6.,   0.);
    btScalar lowerLimit_y = Tools::random(-SIMD_PI/6.,   0.);
    btScalar lowerLimit_z = Tools::random(-SIMD_PI/6.,   0.);

    btScalar upperlimits_x = Tools::random(0.,    SIMD_PI/6.);
    btScalar upperlimits_y = Tools::random(0.,    SIMD_PI/6.);
    btScalar upperlimits_z = Tools::random(0.,    SIMD_PI/6.);

    lowerlimits.insert("x",(double)lowerLimit_x);
    lowerlimits.insert("y",(double)lowerLimit_y);
    lowerlimits.insert("z",(double)lowerLimit_z);

    upperlimits.insert("x",(double)upperlimits_x);
    upperlimits.insert("y",(double)upperlimits_y);
    upperlimits.insert("z",(double)upperlimits_z);

    bone.insert("lowerLimits",lowerlimits);
    bone.insert("upperLimits",upperlimits);

    // End fixation
    bone.insert("endFix",Fixation::generateEmpty());

    QJsonObject data;

    data.insert("typeName", "RotationalMotor");
    data.insert("type", rotationalMotorEffector);

    /*"muscle":{"outs":{
                "x": {"brainOuts": [
                 {"connexionInfo":"SIN...","max":1,"min":0},
                 {"connexionInfo":"SIN...","max":1,"min":0}
                ]},
                "y": {"brainOuts": [
                 {"connexionInfo":"SIN...","max":1,"min":0},
                 {"connexionInfo":"SIN...","max":1,"min":0}
                ]},
                "z":"y": {"brainOuts": [
                 {"connexionInfo":"SIN...","max":1,"min":0},
                 {"connexionInfo":"SIN...","max":1,"min":0}
                ]},
              "type":"RotationalMotor"}*/

    // TODO DO IT BETHER
    QJsonObject bOuts;
    QString motors[] = {"x","y","z"};
    QJsonObject emptyOut;
    emptyOut.insert("connexionInfo", "");
    QJsonArray emptyOutList;
    emptyOutList.append(emptyOut);
    emptyOutList.append(emptyOut);
    for(int i = 0; i < 3; i++) {
        QJsonObject motorMap;
        motorMap.insert("brainOuts", emptyOutList);
        bOuts.insert(motors[i], motorMap);
    }

    data.insert("outs", bOuts);
    bone.insert("muscle", data);

    return bone;
}


// -----------
// -- TOOLS --
// -----------

void Bone::setSelected(bool selected)
{
    body->setSelected(selected);
}

void Bone::setSize(btScalar radius, btScalar length)
{
    btScalar oldLength  = this->getLength();
    body->setSize(radius,length);

    // adapt parent connection
    btVector3 origin = parentCt->getFrameOffsetB().getOrigin();
    btVector3 newor = origin + btVector3(0, btScalar(oldLength*0.5),0) - btVector3(0,btScalar(getLength()*0.5),0);
    parentCt->getFrameOffsetB().setOrigin(newor);

    // adapt children connections
    foreach(Bone *b, endFix->getBones())
        b->getParentConstraint()->getFrameOffsetA().setOrigin(btVector3(btScalar(0.), btScalar(getLength()*0.5 + endFix->getRadius()), btScalar(0.)));
}

void Bone::setEndFixationRadius(btScalar radius)
{
    body->setEndFixationRadius(radius);

    // adapt children connections
    foreach(Bone *b, endFix->getBones())
    {
        b->getParentConstraint()->getFrameOffsetA().setOrigin(btVector3(btScalar(0.), btScalar(getLength()*0.5 + radius), btScalar(0.)));
        b->getParentConstraint()->getFrameOffsetB().setOrigin(btVector3(btScalar(0.), btScalar(-b->getLength()*0.5 - radius), btScalar(0.)));
    }
}

void Bone::setToMinimalOuts(){

    // Angular Limit Motors
    btRotationalLimitMotor *motor;
    for(int i=0;i<3;i++)
    {
        motor = parentCt->getRotationalLimitMotor(i);

        // rigid constraint (no free degrees)
        if(motor->m_loLimit == motor->m_hiLimit)
        {
            disconnectMotor(i);
        }
    }
}

}
