#ifndef OGREBULLETWORLD_H
#define OGREBULLETWORLD_H

#include "classes.h"
#include "world/world.h"
#include <QTimer>
#include <QDebug>
#include "graphic/ogremanager.h"
#include "physics/bulletmanager.h"
#include "world/ogrebulletscene.h"
#include "graphic/defaulteventmanager.h"

namespace GeneLabOgreBullet {

    class OgreBulletWorld : public GeneLabCore::World
    {
        Q_OBJECT
    public:

        OgreBulletWorld(QObject *parent = 0);

        // added by ADC
        OgreBulletWorld(BulletManager* bulletManager, OgreManager* ogreManager, DefaultEventManager *eventsManager, QObject *parent = 0);

        void setBulletManager(BulletManager* bulletManager);
        void setOgreManager(OgreManager* ogreManager);

        // added by ADC
        BulletManager* getBulletManager();
        OgreManager* getOgreManager();

    signals:

    public slots:
        void setup();

        // added by ADC
        // the world manager the time
        void start();
        void stop();
        void update();

    private:
        BulletManager* bulletManager;
        OgreManager*   ogreManager;
        DefaultEventManager *eventsManager;

        OgreBulletScene* scene;

        // Execution timer
        QTimer *stepTimer;
    };

}

#endif // OGREBULLETWORLD_H
