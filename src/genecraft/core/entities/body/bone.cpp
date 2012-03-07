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
#include "bullet/shapes/btPhysBone.h"
#include "btshapesfactory.h"

#include "base/shapes/sphere.h"

#include "entities/effectors/brainoutmotor.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "bullet/shapes/btPhysBone.h"

// Others
#include "tools.h"

// World
#include "bullet/btworld.h"

#include <QVariantMap>


namespace GeneCraftCore {

Bone::Bone(btShapesFactory *shapesFactory, btScalar yAxis, btScalar zAxis, btScalar radius, btScalar length, btScalar endFixRadius, const btTransform &initTransform)
    : QObject(), yAxis(yAxis), zAxis(zAxis), parentFix(NULL), motorsEffector(NULL)
{

    motorModifierData = QVariant();
    parentCt = 0;
    body         = (PhysBone*)shapesFactory->createBone(length, radius, endFixRadius, initTransform);
    // TODO: Fix
    //rigidBody    = NULL;//body->getRigidBody();

    btVector3 position(btScalar(0), length*0.5 + endFixRadius, btScalar(0));
    btTransform endTransform;
    endTransform.setIdentity();
    endTransform.setOrigin(position);

    Sphere* physFix = new Sphere(shapesFactory->getWorld(), endFixRadius, endTransform, body->DENSITY);

    endFix          = new Fixation(shapesFactory, physFix, endFixRadius, endTransform, this);

    this->shapesFactory = shapesFactory;
}

Bone::~Bone()
{
    delete motorsEffector;
    // TODO: fix use physobject
    //shapesFactory->getWorld()->getBulletWorld()->removeConstraint(parentCt);
    delete parentCt;
    delete endFix;
    // TODO: fix use physobject
    //delete this->origin;
    delete body;
}

void Bone::remove() {

//    do it out of here, else bones are remove from fix and can't be deleted because we lose the pointer...
//    if(parentFix != NULL) {
//        parentFix->removeBone(this);
//        parentFix = NULL;
//    }

    endFix->remove();

    if(motorsEffector)
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
    //origin = new RigidBodyOrigin(RigidBodyOrigin::BONE,(QObject *)this);
    //rigidBody->setUserPointer(origin);

    // parent constraint
    if(parentCt)
    {
        // state
        //rigidBody->setActivationState(DISABLE_DEACTIVATION);
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
        if(motorModifierData != QVariant()) {
            QVariantMap motor = motorModifierData.toMap();
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
    if(motorsEffector)
    motorsEffector->setOutputsFrom(1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/);
}

void Bone::setNormalPositionMotors()
{
    if(motorsEffector)
    motorsEffector->setOutputsFrom(0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/);
}

void Bone::setRandomMotors()
{
    if(motorsEffector)
    motorsEffector->setOutputsFrom(2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/);
}

void Bone::resetMotors()
{
    // Angular Limit Motors
    if(parentCt) {
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
}

void Bone::disconnectMotor(int i)
{
    if(motorsEffector)
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

    if(parentCt)
    parentCt->getFrameOffsetA().setRotation(local1);
}

void Bone::setZAxis(btScalar zAxis) {
    this->zAxis = zAxis;
    btQuaternion local1;
    local1.setRotation(btVector3(0, 1, 0), yAxis);
    btQuaternion local2;
    local2.setRotation(btVector3(0, 0, 1), zAxis);
    local1 *= local2;

    if(parentCt)
    parentCt->getFrameOffsetA().setRotation(local1);
}

// -------------------
// -- SERIALIZATION --
// -------------------

QVariant Bone::serialize()
{
    QVariantMap bone;

    // Length & radius
    bone.insert("length",QVariant((double)getLength()));
    bone.insert("radius",QVariant((double)getRadius()));

    // Yaw & Roll
    QVariantMap localRotation;
    localRotation.insert("y",QVariant((double)getYAxis()));
    localRotation.insert("z",QVariant((double)getZAxis()));
    bone.insert("localRotation",localRotation);

    // Limits
    QVariantMap lowerlimits, upperlimits;
    btVector3 angularLowerLimits, angularUpperLimits;
    if(parentCt) {
        parentCt->getAngularLowerLimit(angularLowerLimits);
        parentCt->getAngularUpperLimit(angularUpperLimits);
    }

    lowerlimits.insert("x",QVariant((double)angularLowerLimits.x()));
    lowerlimits.insert("y",QVariant((double)angularLowerLimits.y()));
    lowerlimits.insert("z",QVariant((double)angularLowerLimits.z()));

    upperlimits.insert("x",QVariant((double)angularUpperLimits.x()));
    upperlimits.insert("y",QVariant((double)angularUpperLimits.y()));
    upperlimits.insert("z",QVariant((double)angularUpperLimits.z()));

    bone.insert("lowerLimits",lowerlimits);
    bone.insert("upperLimits",upperlimits);

    // End fixation
    bone.insert("endFix",endFix->serialize());

    if(motorsEffector) // FIXME you can't serialize motorsEffector if entity isn't still setup !
        bone.insert("muscle", this->motorsEffector->serialize());

    return bone;
}

QVariant Bone::generateEmpty() {

    QVariantMap bone;

    // TODO right values ???
    // Length & radius
    bone.insert("length",QVariant((double)Tools::random(0.5,3.0)));
    bone.insert("radius",QVariant((double)Tools::random(0.1,0.5)));

    // Yaw & Roll
    QVariantMap localRotation;
    localRotation.insert("y",QVariant((double)Tools::random(-SIMD_PI,SIMD_PI)));
    localRotation.insert("z",QVariant((double)Tools::random(-SIMD_PI,SIMD_PI)));
    bone.insert("localRotation",localRotation);

    // Limits
    QVariantMap lowerlimits, upperlimits;

    btScalar lowerLimit_x = Tools::random(-SIMD_PI/6.,   0.);
    btScalar lowerLimit_y = Tools::random(-SIMD_PI/6.,   0.);
    btScalar lowerLimit_z = Tools::random(-SIMD_PI/6.,   0.);

    btScalar upperlimits_x = Tools::random(0.,    SIMD_PI/6.);
    btScalar upperlimits_y = Tools::random(0.,    SIMD_PI/6.);
    btScalar upperlimits_z = Tools::random(0.,    SIMD_PI/6.);

    lowerlimits.insert("x",QVariant((double)lowerLimit_x));
    lowerlimits.insert("y",QVariant((double)lowerLimit_y));
    lowerlimits.insert("z",QVariant((double)lowerLimit_z));

    upperlimits.insert("x",(double)upperlimits_x);
    upperlimits.insert("y",(double)upperlimits_y);
    upperlimits.insert("z",(double)upperlimits_z);

    bone.insert("lowerLimits",lowerlimits);
    bone.insert("upperLimits",upperlimits);

    // End fixation
    bone.insert("endFix",Fixation::generateEmpty());

    QVariantMap data;

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
    QVariantMap bOuts;
    QString motors[] = {"x","y","z"};
    QVariantMap emptyOut;
    emptyOut.insert("connexionInfo", "");
    QVariantList emptyOutList;
    emptyOutList.append(emptyOut);
    emptyOutList.append(emptyOut);
    for(int i = 0; i < 3; i++) {
        QVariantMap motorMap;
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


// parents
/**
 * @brief set the parent constraint, the constraint between this bone and the parent fixation
 *
 * @param ct the constraint (bullet) between the bone and the parent fixation
 */
void Bone::setParentConstraint(btGeneric6DofConstraint *ct)   { this->parentCt = ct;          }

/**
 * @brief get the parent constraint, the constraint between this bone and the parent fixation
 *
 * @return btGeneric6DofConstraint * a pt to the constraint between the bone and the parent fixation
 */
btGeneric6DofConstraint * Bone::getParentConstraint()         { return parentCt;              }

/**
 * @brief set the pt to the parent fixation
 *
 * @param parentFix a pt to the parent Fixation*
 */
void Bone::setParentFixation(Fixation *parentFix)             { this->parentFix = parentFix;  }
/**
 * @brief get the pt to the parent fixation
 *
 * @return Fixation * a pt to the parent Fixation
 */
Fixation *Bone::getParentFixation()                           { return parentFix;             }
/**
 * @brief get the pt to the end fixation (the fixation at the end of the bone)
 *
 * @return Fixation * a pt to the Fixation at the end of the bone
 */
Fixation *Bone::getEndFixation()                              { return endFix;                }
/**
 * @brief get the entity where this bone belong
 *
 * @return Entity * a pt to the "parent" entity
 */
Entity *Bone::getEntity()                                     { return entity;                }

// motors
/**
 * @brief get the RotationalMotorsEffector between this bone and the parent fixation
 *
 * @return RotationalMotorsEffector * a pt to the RotationalMotorsEffector between this bone and the parent fixation
 */
RotationalMotorsEffector* Bone::getRotationalMotorsEffector() { return motorsEffector; }
/**
 * @brief the motor modification data, e.g. the genetic code for the brainoutput
 *
 * @param data genetic code for the brain needed data
 */
void Bone::setMotorModifierData(QVariant data)         { this->motorModifierData = data; }

// body & size
/**
 * @brief
 *
 * @return btRigidBody *
 */
//btRigidBody* Bone::getRigidBody()                             { return rigidBody;             }
/**
 * @brief
 *
 * @return btScalar
 */
btScalar Bone::getLength()                                    { return body->getLength();     }
/**
 * @brief
 *
 * @return btScalar
 */
btScalar Bone::getRadius()                                    { return body->getRadius();     }

btScalar Bone::getMass() {
    return this->body->getMass();
}
}
