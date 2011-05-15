#include "ogrebulletentity.h"
#include "struct/treeshape.h"
#include "struct/fixation.h"
#include "struct/articulatedbone.h"
#include "struct/types.h"
#include <QList>
#include <QStack>
#include "core/engine/ogremanager.h"
#include "core/engine/bulletmanager.h"
#include "core/engine/brainengine.h"

#include "core/entity/neural/neuralnetwork.h"

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
