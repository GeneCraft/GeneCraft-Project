#include "treeshape.h"
#include "fixation.h"
#include <QDebug>
#include <QStringBuilder>
#include "treeshape.h"
#include "bone.h"
#include <QList>
#include <QStack>
#include "ogreengine.h"
#include "bulletengine.h"

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

    void TreeShape::initOgreBullet(OgreEngine* ogreManager, BulletEngine *bulletManager)
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

        //getRoot()->initOgreBullet(ogreManager,bulletManager);
        getRoot()->setup(bulletManager);

        // setup recurcively the tree shape
        setupFixation(getRoot());
    }

    void TreeShape::setupFixation(Fixation *fix)
    {
//        // For each bones...
//        QList<Bone*> articulatedBones = fix->getArticulatedBones();
//        Bone *aBone;
//        for(int i=0;i<articulatedBones.length();i++)
//        {
//            // --
//            // -- setup the bone
//            // --


//            aBone = articulatedBones.at(i);
//            //aBone->initOgreBullet();
//            aBone->setup(/*ogreManager,*/bulletManager);                     // create bone and attach the end fixation



//            //fix->addBone(aBone);

//            //aBone->attachToParentFixation(fix); // attach the bone to the parent fixation

//            // setup recurcively
//            setupFixation(aBone->getEndFixation());
//        }
    }

    void TreeShape::print() {
        qDebug() << "Tree shape : ";
        if(root == NULL)
            qDebug() << " empty ";
        else {
            //qDebug() << root->toString();
        }
    }

    void limitFix(Fixation *fix)
    {
        // For each bones...
        QList<Bone*> bones = fix->getBones();
        Bone *aBone;
        for(int i=0;i<bones.length();i++)
        {
             aBone = bones.at(i);
             //aBone->contractInNormalPosition();

             // setup recurcively
             limitFix(aBone->getEndFixation());
        }
    }

    void TreeShape::contractInNormalPosition()
    {
        // setup recurcively the tree shape
        limitFix(getRoot());
    }
}
