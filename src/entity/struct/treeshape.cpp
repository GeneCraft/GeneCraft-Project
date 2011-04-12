#include "treeshape.h"
#include "struct/fixation.h"
#include <QDebug>
#include <QStringBuilder>
#include "struct/treeshape.h"
#include "struct/fixation.h"
#include "struct/articulatedbone.h"
#include "struct/types.h"
#include <QList>
#include <QStack>
#include "graphic/ogremanager.h"
#include "physics/bulletmanager.h"
#include "Dynamics/Constraints/OgreBulletDynamics6DofConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "Dynamics/OgreBulletDynamicsRigidBody.h"
#include "Dynamics/Constraints/OgreBulletDynamicsPoint2pointConstraint.h"

namespace GeneLabOgreBullet {
    TreeShape::TreeShape(QObject *parent) :
        QObject(parent)
    {
        this->root = NULL;
    }

    TreeShape::~TreeShape() {
        delete root;
    }

    void TreeShape::setRoot(Fixation *root) {
        this->root = root;
    }

    Fixation* TreeShape::getRoot() {
        return this->root;
    }

    void TreeShape::initOgreBullet(GeneLabOgreBullet::OgreManager* ogreManager, GeneLabOgreBullet::BulletManager *bulletManager)
    {
        this->ogreManager = ogreManager;
        this->bulletManager = bulletManager;
    }


    void TreeShape::setup()
    {
        // need call initOgreBullet before!
        if(ogreManager == NULL)
        {
            qDebug("ogreManager not initialized, please call initOgreBullet before."); // throw ...
            return;
        }

        if(bulletManager == NULL)
        {
            qDebug("bulletManager not initialized, please call initOgreBullet before."); // throw ...
            return;
        }

        getRoot()->initOgreBullet(ogreManager,bulletManager);
        getRoot()->setup();

        // setup recurcively the tree shape
        setupFixation(getRoot());
    }

    void TreeShape::setupFixation(GeneLabOgreBullet::Fixation *fix)
    {
        // For each bones...
        QList<GeneLabOgreBullet::ArticulatedBone*> articulatedBones = fix->getArticulatedBones();
        GeneLabOgreBullet::ArticulatedBone *aBone;
        for(int i=0;i<articulatedBones.length();i++)
        {
            // --
            // -- setup the bone
            // --
            aBone = articulatedBones.at(i);
            aBone->initOgreBullet(ogreManager,bulletManager);
            aBone->setup();                     // create bone and attach the end fixation
            aBone->attachToParentFixation(fix); // attach the bone to the parent fixation

            // setup recurcively
            setupFixation(aBone->getFixation());
        }
    }

    void TreeShape::print() {
        qDebug() << "Tree shape : ";
        if(root == NULL)
            qDebug() << " empty ";
        else {
            qDebug() << root->toString();
        }
    }

    void limitFix(GeneLabOgreBullet::Fixation *fix)
    {
        // For each bones...
        QList<GeneLabOgreBullet::ArticulatedBone*> articulatedBones = fix->getArticulatedBones();
        GeneLabOgreBullet::ArticulatedBone *aBone;
        for(int i=0;i<articulatedBones.length();i++)
        {
             aBone = articulatedBones.at(i);
             aBone->contractInNormalPosition();

             // setup recurcively
             limitFix(aBone->getFixation());
        }
    }

    void TreeShape::contractInNormalPosition()
    {
        // setup recurcively the tree shape
        limitFix(getRoot());
    }
}
