#include "ogrebulletentity.h"

namespace GeneLabOgreBullet {
    OgreBulletEntity::OgreBulletEntity(QString name, QString f, int gen, QObject *parent) :
        GeneLabCore::Entity(name, f, gen)
    {}

    void OgreBulletEntity::setup() {}

    void OgreBulletEntity::setShape(TreeShape *shape) {
        this->shape = shape;
    }

    TreeShape* OgreBulletEntity::getShape() {
        return this->shape;
    }
}
