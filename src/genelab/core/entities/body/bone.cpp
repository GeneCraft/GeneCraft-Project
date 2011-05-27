#include "bone.h"
#include "fixation.h"
//#include "OgreBulletDynamicsConstraint.h"
//#include "Dynamics/Constraints/OgreBulletDynamics6DofConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "rigidbodyorigin.h"
//#include "openglengine.h"
//#include "openglscene.h"
#include "bulletengine.h"
#include "bonepropertiescontroller.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "tools.h"

// shape
#include "btcylinder.h"
#include "btbone.h"
#include "btshapesfactory.h"
#include "BulletCollision/CollisionShapes/btCompoundShape.h"

#include <QDebug>
#include <QTest>

namespace GeneLabCore {

BonePropertiesController* Bone::inspectorWidget = 0;

Bone::Bone(btShapesFactory *shapesFactory,
           btScalar radius, btScalar length, btScalar endFixRadius, const btTransform &initTransform) : QObject(),
    radius(radius), length(length)
{

    qDebug() << initTransform.getOrigin().x()
             << initTransform.getOrigin().y()
             << initTransform.getOrigin().z() ;

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

    // state
    //this->rigidBody->setDeactivationTime(100.0);
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
/*

    for(int i=0;i<3;i++)
    {
        btRotationalLimitMotor * motor = endFixConstraint->getRotationalLimitMotor(i);
        motor->m_enableMotor = true;
        motor->m_stopERP = 0.01f; // Error tolerance factor when joint is at limit.
        motor->m_stopCFM = 1.f; // Constraint force mixing factor when joint is at limit.
        motor->m_maxMotorForce = 1000.f;
        motor->m_maxLimitForce = 300.f;
        motor->m_targetVelocity = 0;
        motor->m_bounce = 0;
        motor->m_damping = 1;
    }
*/
    // attach to its parent
    bulletEngine->getBulletDynamicsWorld()->addConstraint(parentCt, true);
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

void Bone::setRandomMotors()
{
    // random limits
    float minTargetVelocity = -8.0;
    float maxTargetVelocity = 8.0;

    int minMaxMotorForce = 10;
    int maxMaxMotorForce = 100;

    int minMaxLimitForce = 10;
    int maxMaxLimitForce = 50;

    float minAngularLowerLimit = -3.14;
    float maxAngularLowerLimit = 3.14;

    float minAngularUpperLimit = -3.14;
    float maxAngularUpperLimit = 3.14;

    // Angular Limit Motors
    btRotationalLimitMotor *motor;
    for(int i=0;i<3;i++)
    {
        motor = parentCt->getRotationalLimitMotor(i);

        motor->m_enableMotor    = true;
        motor->m_targetVelocity = btScalar(Tools::random(minTargetVelocity,maxTargetVelocity));
        motor->m_maxMotorForce  = btScalar(Tools::random(minMaxMotorForce,maxMaxMotorForce));
        motor->m_maxLimitForce  = btScalar(Tools::random(minMaxLimitForce,maxMaxLimitForce));
        motor->m_loLimit        = btScalar(Tools::random(minAngularLowerLimit,maxAngularLowerLimit));
        motor->m_hiLimit        = btScalar(Tools::random(minAngularUpperLimit,maxAngularUpperLimit));
    }
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

//namespace GeneLabCore {
//    Bone::Bone(QObject *parent) :
//        QObject(parent)
//    {
//        end = new Fixation();
//    }

//    Bone::~Bone() {
//        delete end;
//    }

//    // TODO alpha min and max
//    Bone::Bone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length) {

//        this->alpha_min = alpha;
//        this->alpha_max = -alpha;
//        this->beta_min = beta_min;
//        this->beta_max = beta_max;
//        this->r_min = r_min;
//        this->r_max = r_max;
//        this->boneLength = length;
//        this->boneRadius = 0.05;
//        this->boneMass = 0.1;

//        end = new Fixation();
//    }

//    float Bone::getLength() {
//        return this->boneLength;
//    }

//    float Bone::rotationCapacity() {
//        return r_max - r_min;
//    }

//    float Bone::hingeCapacity() {
//        return beta_max - beta_min;
//    }

//    float Bone::getAlpha() {
//        return alpha_max;
//    }

//    float Bone::getBetaMin() {
//        return beta_min;
//    }

//    Fixation* Bone::getFixation() {
//        return end;
//    }

//    OgreBulletDynamics::RigidBody *Bone::getRigidBody()
//    {
//        return this->rigidBody;
//    }

//    void Bone::initOgreBullet(OgreManager* ogreManager, BulletManager *bulletManager)
//    {
//        this->ogreManager = ogreManager;
//        this->bulletManager = bulletManager;
//    }

//    void Bone::setup()
//    {
//        // create the bones
//        this->rigidBody = SandboxTools::addBox(ogreManager,bulletManager,Ogre::Vector3(0,9,0),Ogre::Vector3(this->boneRadius,this->boneLength,this->boneRadius));

//        // attach fixation to bones
//        end->initOgreBullet(ogreManager,bulletManager);
//        end->setup(Ogre::Vector3(0,3,0)); // TODO

//        // attach articulatedBone to its fixation
//        OgreBulletDynamics::SixDofConstraint *ctBoneToSonFix = new OgreBulletDynamics::SixDofConstraint(
//                end->getRigidBody(),getRigidBody(),Ogre::Vector3(0,0,0),Ogre::Quaternion(),Ogre::Vector3(0,-(getLength()/2.0+end->getRadius()/2.0),0),Ogre::Quaternion());

//        // constraint articulation
//        static_cast<btGeneric6DofConstraint* > (ctBoneToSonFix->getBulletTypedConstraint())->setAngularLowerLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,0,0)));
//        static_cast<btGeneric6DofConstraint* > (ctBoneToSonFix->getBulletTypedConstraint())->setAngularUpperLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,0,0)));

//        bulletManager->getWorld()->addConstraint(ctBoneToSonFix);
//    }

//    QString Bone::toString() {
//        return "-" + QString::number(boneLength) + "-" + this->end->toString();
//    }

//    void Bone::attachToParentFixation(Fixation* parentFix)
//    {
//        // attach the bone to the parent fixation
//        parentSixDofConstraint = new OgreBulletDynamics::SixDofConstraint(parentFix->getRigidBody(),
//                                                                          getRigidBody(),
//                                                                          Ogre::Vector3(0,0,0),
//                                                                          Ogre::Quaternion(),
//                                                                          Ogre::Vector3(0,getLength()/2.0+end->getRadius()/2.0,0),
//                                                                          Ogre::Quaternion());

//        bulletManager->getWorld()->addConstraint(parentSixDofConstraint);

//        // configure the attachement
//        btGeneric6DofConstraint *ctParentFixToBone_b = (btGeneric6DofConstraint*) parentSixDofConstraint->getBulletTypedConstraint();

//        // OgreBulletDynamics::SixDofConstraint::setAngularLowerLimit isn't correct ! We use directly Bullet methods
//        ctParentFixToBone_b->setAngularLowerLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(1,-1.5,1)));
//        ctParentFixToBone_b->setAngularUpperLimit(OgreBulletCollisions::OgreBtConverter::to (Ogre::Vector3(0,1.5,0)));

//        for(int i=0;i<1;i++)
//        {
//            if (i == 1)
//                continue;

//            btRotationalLimitMotor *motor = ctParentFixToBone_b->getRotationalLimitMotor(i);
//            motor->m_enableMotor = true;
//            motor->m_targetVelocity = 20;
//            motor->m_maxMotorForce = 1000;
//        }
//    }

//    void Bone::contractInNormalPosition()
//    {
//        // configure the attachement
//        btGeneric6DofConstraint *ctParentFixToBone_b = (btGeneric6DofConstraint*) parentSixDofConstraint->getBulletTypedConstraint();

//        //ctParentFixToBone_b->setAngularLowerLimit(btVector3(0,0,0));
//        //ctParentFixToBone_b->setAngularUpperLimit(btVector3(0,0,0));

//        //ctParentFixToBone_b->setAngularLowerLimit(btVector3(alpha,beta_max - beta_min,r_max - r_min));
//        //ctParentFixToBone_b->setAngularUpperLimit(btVector3(alpha,beta_max - beta_min,r_max - r_min));

//        for(int i=0;i<3;i++)
//        {
//            btRotationalLimitMotor *motor = ctParentFixToBone_b->getRotationalLimitMotor(i);

//            motor->m_hiLimit = 0;
//            motor->m_loLimit = 0;
//            motor->m_maxLimitForce = 100000;
//            motor->m_enableMotor = true;
//            motor->m_targetVelocity = 0;
//            motor->m_maxMotorForce = 1;
//        }
//    }
//}
