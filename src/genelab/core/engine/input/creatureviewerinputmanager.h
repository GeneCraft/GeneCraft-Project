#ifndef CREATUREVIEWERINPUTMANAGER_H
#define CREATUREVIEWERINPUTMANAGER_H

#include "classes.h"
#include "inputlistener.h"

namespace GeneLabCore {
    class CreatureViewerInputManager : public InputListener
    {
    public:
        CreatureViewerInputManager();

        // Events (must be call during beforeStep)
        void mousePressEvent(QMouseEvent * e);
        void mouseReleaseEvent(QMouseEvent * e);
        void mouseMoveEvent(QMouseEvent * e);
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);
        void enterViewPortEvent(QEvent *e);
        void leaveViewPortEvent(QEvent *e);

        void initOgreBullet(OgreManager* ogreManager,BulletManager *bulletManager,Ogre::Camera *camera);

    private:

        void throwCube();
        Ogre::Camera *camera;
        OgreManager* ogreManager;
        BulletManager *bulletManager;
        int mNumEntitiesInstanced;

    };
}

#endif // CREATUREVIEWERINPUTMANAGER_H
