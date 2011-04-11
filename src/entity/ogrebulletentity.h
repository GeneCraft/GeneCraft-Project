#ifndef OGREBULLETENTITY_H
#define OGREBULLETENTITY_H

#include "classes.h"
#include "entity/entity.h"

namespace GeneLabOgreBullet {

    class OgreBulletEntity : public GeneLabCore::Entity
    {
        Q_OBJECT
    public:
        explicit OgreBulletEntity(QString name, QString f, int gen, QObject *parent = 0);

    signals:

    public slots:
        void initOgreBullet(OgreManager* ogreManager, BulletManager* bulletManager);
        void setup();
        void setShape(TreeShape* shape);
        TreeShape* getShape();

    private:
        TreeShape* shape;
        OgreManager *ogreManager;
        BulletManager *bulletManager;

        void setupFixation(GeneLabOgreBullet::Fixation *fix);
    };

}
#endif // OGREBULLETENTITY_H
