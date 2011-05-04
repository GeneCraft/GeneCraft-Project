#ifndef OGREBULLETSCENE_H
#define OGREBULLETSCENE_H

#include <QObject>
#include "classes.h"
namespace GeneLabOgreBullet {
    class OgreBulletScene : public QObject
    {
        Q_OBJECT
    public:

        OgreBulletScene(BulletManager* bulletManager, OgreManager* ogreManager, QObject *parent = 0);

        void init();

    signals:

    public slots:

    protected:
        BulletManager* bulletManager;
        OgreManager* ogreManager;
    };
}
#endif // OGREBULLETSCENE_H
