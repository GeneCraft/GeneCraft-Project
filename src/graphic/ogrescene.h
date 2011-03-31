#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include "classes.h"

namespace GeneLabOgreBullet {
    class OgreScene : public QObject
    {
        Q_OBJECT
    public:
        explicit OgreScene(Ogre::Root* ogreRoot,
                           Ogre::SceneManager* sceneManager);

        // Add and remove of world, entity
        /*void addWorld(GeneLabCore::World* world);
        void addEntity(GeneLabCore::Entity* entity);
        void removeWorld(GeneLabCore::World* world);
        void removeEntity(GeneLabCore::Entity* entity);*/

    signals:

    public slots:

    protected:
        Ogre::Root* ogreRoot;
        Ogre::SceneManager* sceneManager;

    };
}
#endif // SCENEMANAGER_H
