#include "ogrebulletentity.h"

namespace GeneLabOgreBullet {
    OgreBulletEntity::OgreBulletEntity(QString name, QString f, int gen, QObject *parent) :
        GeneLabCore::Entity(name, f, gen)
    {}

    void OgreBulletEntity::setup() {}
}
