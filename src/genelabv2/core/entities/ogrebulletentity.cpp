#include "ogrebulletentity.h"
#include "treeshape.h"
#include "fixation.h"
#include "bone.h"
#include <QList>
#include <QStack>
#include "ogremanager.h"
#include "bulletmanager.h"
#include "brainengine.h"
#include "neuralnetwork.h"

namespace GeneLabCore {
    OgreBulletEntity::OgreBulletEntity(QString name, QString f, int gen, QObject *parent) :
        GeneLabCore::Entity(name, f, gen)
    {}

    void OgreBulletEntity::init(OgreManager* ogreManager, BulletManager* bulletManager,
                                          BrainEngine* brainEngine)
    {
        this->ogreManager = ogreManager;
        this->bulletManager = bulletManager;
        this->brainEngine = brainEngine;

        // TODO add ogreManager and bulletManager to all fixation...
    }

    void OgreBulletEntity::setup()
    {
        // Setup the shape
        shape->initOgreBullet(ogreManager,bulletManager);
        shape->setup();

        this->brain = brainEngine->addNetwork(10); // 10x10 network
        this->brain->animate(shape);
    }

    void OgreBulletEntity::setShape(TreeShape *shape) {
        this->shape = shape;
    }

    TreeShape* OgreBulletEntity::getShape() {
        return this->shape;
    }
}
