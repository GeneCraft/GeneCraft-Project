#include "bone.h"

// Qt
#include <QDebug>
#include <QTest>
#include "widgets/entities/bonepropertiescontroller.h"

// Entity
#include "entity.h"
#include "body/fixation.h"
#include "modifiers/rotationalmotorsmodifier.h"

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
#include "world/btworld.h"


namespace GeneLabCore {

BonePropertiesController* Bone::inspectorWidget = 0;

Bone::Bone(btShapesFactory *shapesFactory, btScalar yAxis, btScalar zAxis, btScalar radius, btScalar length, btScalar endFixRadius, const btTransform &initTransform)
    : QObject(), yAxis(yAxis), zAxis(zAxis), motorsModifier(NULL)
{

    motorModifierData = QVariant(0);
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
    delete body;
    delete origin;
    delete endFix;
    delete motorsModifier;

    shapesFactory->getWorld()->getBulletWorld()->removeConstraint(parentCt);
    delete parentCt;
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
            motor->m_stopERP = 0.1f; // Error tolerance factor when joint is at limit.
            motor->m_stopCFM = 1.f; // Constraint force mixing factor when joint is at limit.
            motor->m_maxMotorForce = 0.001f;
            motor->m_maxLimitForce = 0.001f;
            motor->m_targetVelocity = 0;
            motor->m_bounce = 0.9;
            motor->m_damping = 0.9;
        }

        // add motor modifier
        if(motorModifierData != QVariant(0))
            motorsModifier = new RotationalMotorsModifier(motorModifierData, parentCt);
        else
            motorsModifier = new RotationalMotorsModifier(parentCt);

        if(entity)
           entity->addLinkToModifier(motorsModifier);

        // attach to its parent
        shapesFactory->getWorld()->getBulletWorld()->addConstraint(parentCt, true);
    }

    //bulletEngine->getBulletDynamicsWorld()->addConstraint(endFixConstraint, true);
    endFix->setup();
}


BonePropertiesController *Bone::getInspectorWidget()
{
    if(inspectorWidget == 0)
        inspectorWidget = new BonePropertiesController();

    inspectorWidget->setBone(this);

    return inspectorWidget;
}

BonePropertiesController *Bone::getEmptyInspectorWidget()
{
    if(inspectorWidget == 0)
        inspectorWidget = new BonePropertiesController();

    return inspectorWidget;
}

void Bone::setEntity(Entity *entity)
{
    this->entity = entity;

    endFix->setEntity(entity);
}

void Bone::disableMotors()
{
    motorsModifier->disable();
}

void Bone::setBrainMotors()
{
    motorsModifier->setOutputsFrom(1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/);
}

void Bone::setNormalPositionMotors()
{
    motorsModifier->setOutputsFrom(0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/);
}

void Bone::setRandomMotors()
{
    motorsModifier->setOutputsFrom(2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/);
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

void Bone::setyAxis(btScalar yAxis) {
    this->yAxis = yAxis;
    btQuaternion local1;
    local1.setRotation(btVector3(0, 1, 0), yAxis);
    btQuaternion local2;
    local2.setRotation(btVector3(0, 0, 1), zAxis);
    local1 *= local2;

    parentCt->getFrameOffsetA().setRotation(local1);
}

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
    parentCt->getAngularLowerLimit(angularLowerLimits);
    parentCt->getAngularUpperLimit(angularUpperLimits);

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

    bone.insert("muscle", this->motorsModifier->serialize());

    return bone;
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

}
