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



namespace GeneLabCore {

BonePropertiesController* Bone::inspectorWidget = 0;

Bone::Bone(btShapesFactory *shapesFactory,
           btScalar yAxis, btScalar zAxis, btScalar radius, btScalar length, btScalar endFixRadius, const btTransform &initTransform) : QObject(),
    yAxis(yAxis), zAxis(zAxis), radius(radius), length(length), motorsModifier(NULL)
{

    motorModifierData = QVariant(0);
    parentCt = 0;
    bulletEngine = shapesFactory->getBulletEngine();
    body        = shapesFactory->createBone(length, radius, endFixRadius, initTransform);
    rigidBody   = body->getRigidBody();


    btVector3 position(btScalar(0), length/2 + endFixRadius, btScalar(0));
    btTransform endTransform;
    endTransform.setIdentity();
    endTransform.setOrigin(position);

    endFix      = new Fixation(shapesFactory, rigidBody, endFixRadius, endTransform);
}

Bone::~Bone()
{
    //openGLEngine->getScene()->removeDrawableObject(body); TODO
    //bulletEngine->getBulletDynamicsWorld()->removeRigidBody(this->rigidBody);

    // constraint
    //bulletEngine->getBulletDynamicsWorld()->removeConstraint(endFixConstraint);
    delete endFixConstraint;

    //bulletEngine->getBulletDynamicsWorld()->removeConstraint(parentCt);
    delete parentCt;

    delete body;
    delete endFix;
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
            motor->m_stopERP = 0.01f; // Error tolerance factor when joint is at limit.
            motor->m_stopCFM = 1.f; // Constraint force mixing factor when joint is at limit.
            motor->m_maxMotorForce = 1000.f;
            motor->m_maxLimitForce = 300.f;
            motor->m_targetVelocity = 0;
            motor->m_bounce = 0;
            motor->m_damping = 1;
        }

        // add motor modifier
        if(motorModifierData != QVariant(0))
            motorsModifier = new RotationalMotorsModifier(motorModifierData, parentCt);
        else
            motorsModifier = new RotationalMotorsModifier(parentCt);

        if(entity)
           entity->addLinkToModifier(motorsModifier);

        // attach to its parent
        bulletEngine->getBulletDynamicsWorld()->addConstraint(parentCt, true);
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
    bone.insert("length",QVariant((double)length));
    bone.insert("radius",QVariant((double)radius));

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
}
