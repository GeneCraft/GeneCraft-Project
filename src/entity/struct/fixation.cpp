#include "fixation.h"
#include "entity/struct/articulatedbone.h"
#include <QStringBuilder>
#include "sandboxtools.h"

namespace GeneLabOgreBullet {
    Fixation::Fixation(QObject *parent) :
        QObject(parent)
    {
    }

    Fixation::~Fixation() {
        while(!articulatedBones.isEmpty()) {
            ArticulatedBone* b = articulatedBones.takeFirst();
            delete b;
        }
    }

    ArticulatedBone* Fixation::addBone(float alpha, float beta, float length) {
        return this->addBone(alpha, beta, beta, 0, 0, length);
    }

    ArticulatedBone* Fixation::addBone(float alpha, float beta, float r_min, float r_max, float length) {
        return this->addBone(alpha, beta, beta, r_min, r_max, length);
    }

    ArticulatedBone* Fixation::addBone(float alpha, float beta_min, float beta_max, float length) {
        return this->addBone(alpha, beta_min, beta_max, 0, 0, length);
    }

    ArticulatedBone* Fixation::addBone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length) {
        ArticulatedBone* b = new ArticulatedBone(alpha, beta_min, beta_max, r_min, r_max, length);
        this->articulatedBones.append(b);
        return b;
    }

    QList<ArticulatedBone*> Fixation::getArticulatedBones() {
        return articulatedBones;
    }

    OgreBulletDynamics::RigidBody *Fixation::getRigidBody()
    {
        return this->rigidBody;
    }

    void Fixation::initOgreBullet(GeneLabOgreBullet::OgreManager* ogreManager, GeneLabOgreBullet::BulletManager *bulletManager)
    {
        this->ogreManager = ogreManager;
        this->bulletManager = bulletManager;
    }


    void Fixation::setup()
    {
        this->rigidBody = SandboxTools::addSphere(ogreManager,bulletManager,Ogre::Vector3(0,30,0),1);
    }

    QString Fixation::toString() {
        QString b;
        b += "O";
        if(articulatedBones.length() > 1) {
            b += "{";
            for(int i = 0; i < articulatedBones.length(); i++) {
                b += articulatedBones[i]->toString();
                if(i+1 < articulatedBones.length())
                    b+= ",";
            }
            b += "}";
        }
        else if(articulatedBones.length() == 1)
            b += articulatedBones.first()->toString();
        b += "";
        return b;
    }
}
