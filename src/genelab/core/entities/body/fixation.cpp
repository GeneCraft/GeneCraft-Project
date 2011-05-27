#include "fixation.h"
#include "bone.h"
#include <QStringBuilder>
#include "fixationproperties.h"
#include "bulletengine.h"
#include "rigidbodyorigin.h"
#include "btshapesfactory.h"
#include "btsphere.h"

#include <QDebug>

namespace GeneLabCore {

    FixationProperties* Fixation::inspectorWidget = 0;
    const btScalar Fixation::PERCENT_BONE_INSIDE_FIX = 0.15f;

    #define FIXATION_DENSITY 5.0f
    #define FIXATION_FRICTION 0.6f

    Fixation::Fixation(btShapesFactory *shapesFactory,
                       btRigidBody* body,
                       btScalar radius,
                       btTransform localFixation) {
        this->shapesFactory = shapesFactory;
        this->rigidBody = body;
        this->localFixation.setIdentity();
        this->localFixation = localFixation;
        this->radius = radius;
        airFixation = 0;
        entity = 0;
        delegatedSetup = true;
        qDebug() << "fixation created !";
    }

    Fixation::Fixation(btShapesFactory *shapesFactory,
                       btScalar radius,
                       btTransform initTransform) : QObject(), radius(radius), airFixation(0), entity(0)
    {
        this->shapesFactory = shapesFactory;
        this->localFixation.setIdentity();

        sphere = shapesFactory->createSphere(radius, initTransform); // btScalar(FIXATION_DENSITY)
        rigidBody = sphere->getRigidBody();
        rigidBody->setFriction(FIXATION_FRICTION);
        delegatedSetup = false;
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
        if(!delegatedSetup) {

            // shape
            sphere->setup();

            // origins
            origin = new RigidBodyOrigin(RigidBodyOrigin::FIXATION,(QObject *)this);
            rigidBody->setUserPointer(origin);

            // state
            //rigidBody->setDeactivationTime(100.0);
            rigidBody->setActivationState(DISABLE_DEACTIVATION);
        }


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

    Bone *Fixation::addBone(const btQuaternion &localOrientation,
                            btScalar boneRadius,
                            btScalar boneLenght,
                            btScalar endFixRadius,
                            const btVector3 &lowerLimits,
                            const btVector3 &upperLimits)
    {
        // Get the initial transform
        btTransform initTransform = this->rigidBody->getWorldTransform();
        if(initTransform.getOrigin().getX() > 1000) {
            qDebug() << initTransform.getOrigin().x() << " " << initTransform.getOrigin().y() << " " << initTransform.getOrigin().z();
            int toto;
        }
        initTransform *= localFixation;
        initTransform.setRotation(initTransform.getRotation()*localOrientation);

        btVector3 newPos(0, btScalar((boneLenght*0.5 + radius)), 0);
        btVector3 transposedPos = initTransform*newPos;

        btTransform boneTransform;
        boneTransform.setIdentity();

        boneTransform.setRotation(initTransform.getRotation());
        boneTransform.setOrigin(transposedPos);

        Bone * bone = new Bone(shapesFactory, boneRadius, boneLenght, endFixRadius, boneTransform);

        btTransform localBone;
        localBone.setIdentity();
        localBone.setOrigin(btVector3(btScalar(0.), btScalar(-bone->getLength()*0.5 -radius), btScalar(0.)));

        btTransform localFix;
        localFix.setIdentity();
        localFix.setRotation(localOrientation);
        localFix.setOrigin(localFixation.getOrigin());

        btGeneric6DofConstraint * ct = new btGeneric6DofConstraint(*this->rigidBody,*bone->getRigidBody(),
                                                                   localFix, localBone, true);
        ct->setAngularLowerLimit(lowerLimits);
        ct->setAngularUpperLimit(upperLimits);
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
