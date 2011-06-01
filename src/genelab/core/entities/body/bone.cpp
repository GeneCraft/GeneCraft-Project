#include "bone.h"

// Qt
#include <QDebug>
#include <QTest>
#include "bonepropertiescontroller.h"

// Entity
#include "entity.h"
#include "fixation.h"
#include "rotationalmotorsmodifier.h"

// Engine
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "rigidbodyorigin.h"
#include "bulletengine.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "BulletCollision/CollisionShapes/btCompoundShape.h"
#include "btcylinder.h"
#include "btbone.h"
#include "btshapesfactory.h"

// Others
#include "tools.h"



namespace GeneLabCore {

BonePropertiesController* Bone::inspectorWidget = 0;

Bone::Bone(btShapesFactory *shapesFactory,
           btScalar radius, btScalar length, btScalar endFixRadius, const btTransform &initTransform) : QObject(),
    radius(radius), length(length), endFix(NULL), motorsModifier(NULL), parentCt(NULL)
{

    bulletEngine = shapesFactory->getBulletEngine();

    body        = shapesFactory->createBone(length,radius, endFixRadius, initTransform);
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
    motorsModifier->setOutputsFrom(RotationalMotorsModifier::OUTPUTS_FROM_BRAIN);
}

void Bone::setNormalPositionMotors()
{
    motorsModifier->setOutputsFrom(RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION);
}

void Bone::setRandomMotors()
{
    motorsModifier->setOutputsFrom(RotationalMotorsModifier::OUTPUTS_FROM_RANDOM);
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
}
