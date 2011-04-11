#include "articulatedbone.h"
#include "entity/struct/fixation.h"
#include "sandboxtools.h"

namespace GeneLabOgreBullet {
    ArticulatedBone::ArticulatedBone(QObject *parent) :
        QObject(parent)
    {
        end = new Fixation();
    }

    ArticulatedBone::~ArticulatedBone() {
        delete end;
    }

    ArticulatedBone::ArticulatedBone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length) {
        this->alpha = alpha;
        this->beta_min = beta_min;
        this->beta_max = beta_max;
        this->r_min = r_min;
        this->r_max = r_max;
        this->length = length;

        end = new Fixation();
    }

    float ArticulatedBone::getLength() {
        return this->length;
    }

    float ArticulatedBone::rotationCapacity() {
        return r_max - r_min;
    }

    float ArticulatedBone::hingeCapacity() {
        return beta_max - beta_min;
    }

    float ArticulatedBone::getAlpha() {
        return alpha;
    }

    float ArticulatedBone::getBeta() {
        return beta_min;
    }

    Fixation* ArticulatedBone::getFixation() {
        return end;
    }

    OgreBulletDynamics::RigidBody *ArticulatedBone::getRigidBody()
    {
        return this->rigidBody;
    }

    void ArticulatedBone::initOgreBullet(GeneLabOgreBullet::OgreManager* ogreManager, GeneLabOgreBullet::BulletManager *bulletManager)
    {
        this->ogreManager = ogreManager;
        this->bulletManager = bulletManager;
    }

    void ArticulatedBone::setup()
    {
        this->rigidBody = SandboxTools::addBox(ogreManager,bulletManager,Ogre::Vector3(0,9,0),Ogre::Vector3(0.2,this->length,0.2));
    }

    QString ArticulatedBone::toString() {
        return "-" + QString::number(length) + "-" + this->end->toString();
    }
}
