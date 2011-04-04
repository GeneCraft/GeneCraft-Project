#include "ogrebulletscene.h"
namespace GeneLabOgreBullet {
    using namespace GeneLabCore;

    OgreBulletScene::OgreBulletScene(BulletManager* bulletManager, OgreManager* ogreManager, QObject *parent) :
            QObject(parent)
    {
        this->bulletManager = bulletManager;
        this->ogreManager = ogreManager;
    }
}
