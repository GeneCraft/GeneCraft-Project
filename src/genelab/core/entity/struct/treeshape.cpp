#include "treeshape.h"
#include "core/entity/struct/fixation.h"
#include <QDebug>
#include <QStringBuilder>
#include "core/entity/struct/treeshape.h"
#include "core/entity/struct/articulatedbone.h"
#include "core/entity/struct/types.h"
#include <QList>
#include <QStack>
#include "core/engine/ogremanager.h"
#include "core/engine/bulletmanager.h"

#include "OGRE/Ogre.h"

namespace GeneLabCore {
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

    void TreeShape::initOgreBullet(OgreManager* ogreManager, BulletManager *bulletManager)
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
        getRoot()->setup(Ogre::Vector3(0,3,0));

        // setup recurcively the tree shape
        setupFixation(getRoot());
    }

    void TreeShape::setupFixation(Fixation *fix)
    {
        // For each bones...
        QList<ArticulatedBone*> articulatedBones = fix->getArticulatedBones();
        ArticulatedBone *aBone;
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

    void limitFix(Fixation *fix)
    {
        // For each bones...
        QList<ArticulatedBone*> articulatedBones = fix->getArticulatedBones();
        ArticulatedBone *aBone;
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
