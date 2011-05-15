#ifndef OGREBULLETENTITYFAMILY_H
#define OGREBULLETENTITYFAMILY_H

#include "classes.h"
#include "core/entity/entityfamily.h"

namespace GeneLabCore {

    class OgreBulletEntityFamily : public GeneLabCore::EntityFamily
    {
        Q_OBJECT
    public:
        explicit OgreBulletEntityFamily(QObject *parent = 0);

        virtual OgreBulletEntity* createOgreBulletEntity() = 0;

        virtual GeneLabCore::Entity* createEntity() {
            return (GeneLabCore::Entity*)createOgreBulletEntity();
        }

    signals:

    public slots:

    };

}
#endif // OGREBULLETENTITYFAMILY_H
