#ifndef OGREBULLETENTITY_H
#define OGREBULLETENTITY_H

#include "classes.h"
#include "entity/entity.h"
#include "struct/treeshape.h"
#include "struct/fixation.h"
#include "struct/bone.h"
#include "struct/types.h"
#include <QList>
#include <QStack>
#include "graphic/ogremanager.h"
#include "physics/bulletmanager.h"

namespace GeneLabOgreBullet {

    class OgreBulletEntity : public GeneLabCore::Entity
    {
        Q_OBJECT
    public:
        explicit OgreBulletEntity(QString name, QString f, int gen, QObject *parent = 0);

    signals:

    public slots:
        void setup(OgreManager* ogreManager, BulletManager* bulletManager);
        void setShape(TreeShape* shape);
        TreeShape* getShape();

    private:
        TreeShape* shape;

    };

}
#endif // OGREBULLETENTITY_H
