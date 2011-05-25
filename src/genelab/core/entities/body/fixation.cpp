#include "fixation.h"
#include "bone.h"
#include <QStringBuilder>
#include "sandboxtools.h"
#include "fixationproperties.h"
#include "bulletengine.h"
#include "rigidbodyorigin.h"
#include "btshapesfactory.h"
#include "btsphere.h"

namespace GeneLabCore {

    FixationProperties* Fixation::inspectorWidget = 0;
    const btScalar Fixation::PERCENT_BONE_INSIDE_FIX = 0.15f;

    #define FIXATION_DENSITY 5.0f
    #define FIXATION_FRICTION 0.6f

    Fixation::Fixation(btShapesFactory *shapesFactory, btScalar radius, btVector3 position) : QObject(), radius(radius), airFixation(0), entity(0)
    {
        this->shapesFactory = shapesFactory;

        sphere = shapesFactory->createSphere(radius,position); // btScalar(FIXATION_DENSITY)
        rigidBody = sphere->getRigidBody();
        rigidBody->setFriction(FIXATION_FRICTION);
    }

    Fixation::~Fixation()
    {
        while(bones.size())
        {
            delete bones.at(0);
            bones.removeAt(0);
        }

        delete sphere;
    }

    void Fixation::setup()
    {
        // shape
        sphere->setup();

        // origins
        origin = new RigidBodyOrigin(RigidBodyOrigin::FIXATION,(QObject *)this);
        rigidBody->setUserPointer(origin);

        // state
        //rigidBody->setDeactivationTime(100.0);
        rigidBody->setActivationState(DISABLE_DEACTIVATION);

        for(int i=0;i<bones.size();++i)
            bones.at(i)->setup();
    }

    btRigidBody* Fixation::getRigidBody()
    {
        return this->rigidBody;
        //return this->rigidBody;
    }

    void Fixation::setSelected(bool isSelected)
    {
        //sphere->setSelected(isSelected);
    }

    void Fixation::fixeInTheAir(const btVector3 &position)
    {
//        this->rigidBody->getWorldTransform().setOrigin(position);

//        // fixe root in the air
//        btTransform local; local.setIdentity();
//        btGeneric6DofConstraint *ct = new btGeneric6DofConstraint(*this->rigidBody,local,true);
//        ct->setAngularLowerLimit(btVector3(0,0,0));
//        ct->setAngularUpperLimit(btVector3(0,0,0));
//        airFixation = ct;

//        if(bulletEngine)
//            bulletEngine->getBulletDynamicsWorld()->addConstraint(ct);
//        else
//            qDebug() << "set before (bulletEngine is null)";
    }

    void Fixation::unfixInTheAir()
    {
//        if(bulletEngine != 0 && airFixation != 0)
//        {
//            bulletEngine->getBulletDynamicsWorld()->removeConstraint(airFixation);
//            delete airFixation;
//        }
    }

    Bone *Fixation::addBone(const btTransform &localFix, btScalar boneRadius, btScalar boneLenght, btScalar endFixRadius, const btVector3 &lowerLimits, const btVector3 &upperLimits)
    {
        Bone * bone = new Bone(shapesFactory, boneRadius, boneLenght, endFixRadius, btVector3(this->rigidBody->getWorldTransform().getOrigin()));

        btTransform localBone; localBone.setIdentity();
        localBone.getBasis().setEulerZYX(0,0,0);
        localBone.setOrigin(btVector3(btScalar(0.), btScalar(-(bone->getLength()*0.5 + radius - radius*PERCENT_BONE_INSIDE_FIX)), btScalar(0.)));

        btGeneric6DofConstraint * ct = new btGeneric6DofConstraint(*this->rigidBody,*bone->getRigidBody(),
                                                                   localFix, localBone,true);

        ct->setAngularLowerLimit(lowerLimits);
        ct->setAngularUpperLimit(upperLimits);

        //bulletEngine->getDynamicsWorld()->addConstraint(ct);
        bone->setParentConstraint(ct);
        bone->setEntity(entity);

        bones.append(bone);

        return bone;
    }

    FixationProperties *Fixation::getInspectorWidget()
    {
        if(inspectorWidget == 0)
            inspectorWidget = new FixationProperties();

        inspectorWidget->setFixation(this);

        return inspectorWidget;
    }

//    Fixation::Fixation(QObject *parent) :
//        QObject(parent)
//    {
//        radius = 0.1;
//    }

//    Fixation::~Fixation() {
//        while(!articulatedBones.isEmpty()) {
//            Bone* b = articulatedBones.takeFirst();
//            delete b;
//        }
//    }

//    Bone* Fixation::addBone(float alpha, float beta, float length) {
//        return this->addBone(alpha, beta, beta, 0, 0, length);
//    }

//    Bone* Fixation::addBone(float alpha, float beta, float r_min, float r_max, float length) {
//        return this->addBone(alpha, beta, beta, r_min, r_max, length);
//    }

//    Bone* Fixation::addBone(float alpha, float beta_min, float beta_max, float length) {
//        return this->addBone(alpha, beta_min, beta_max, 0, 0, length);
//    }

//    Bone* Fixation::addBone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length) {
//        Bone* b = new Bone(alpha, beta_min, beta_max, r_min, r_max, length);
//        this->articulatedBones.append(b);
//        return b;
//    }

//    QList<Bone*> Fixation::getArticulatedBones() {
//        return articulatedBones;
//    }

//    OgreBulletDynamics::RigidBody *Fixation::getRigidBody()
//    {
//        return this->rigidBody;
//    }

//    void Fixation::initOgreBullet(OgreManager* ogreManager, BulletManager *bulletManager)
//    {
//        this->ogreManager = ogreManager;
//        this->bulletManager = bulletManager;
//    }

//    void Fixation::setup(Ogre::Vector3 position)
//    {
//        this->rigidBody = SandboxTools::addSphere(ogreManager,bulletManager,position,radius);
//    }

//    QString Fixation::toString() {
//        QString b;
//        b += "O";
//        if(articulatedBones.length() > 1) {
//            b += "{";
//            for(int i = 0; i < articulatedBones.length(); i++) {
//                b += articulatedBones[i]->toString();
//                if(i+1 < articulatedBones.length())
//                    b+= ",";
//            }
//            b += "}";
//        }
//        else if(articulatedBones.length() == 1)
//            b += articulatedBones.first()->toString();
//        b += "";
//        return b;
//    }


//    float Fixation::getRadius()
//    {
//        return radius;
//    }
}
