#include "ogrebulletentity.h"

namespace GeneLabOgreBullet {
    OgreBulletEntity::OgreBulletEntity(QString name, QString f, int gen, QObject *parent) :
        GeneLabCore::Entity(name, f, gen)
    {}

    void OgreBulletEntity::setup(OgreManager* ogreManager, BulletManager* bulletManager)
    {
        GeneLabOgreBullet::TreeShape *shape = this->getShape();

        // Browse the treeshape
        QStack<GeneLabOgreBullet::Fixation *> stack;
        stack.push(shape->getRoot());

        GeneLabOgreBullet::Fixation * fix;
        while(!stack.empty())
        {
            fix = stack.pop();

            QList<Bone*> bones = fix->getBones();

            for(int i=0;i<bones.length();i++)
                stack.push(bones.at(i)->getFixation());
        }
    }

    void OgreBulletEntity::setShape(TreeShape *shape) {
        this->shape = shape;
    }

    TreeShape* OgreBulletEntity::getShape() {
        return this->shape;
    }
}
