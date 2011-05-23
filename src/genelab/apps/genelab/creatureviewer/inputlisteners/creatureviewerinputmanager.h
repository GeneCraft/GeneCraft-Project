#ifndef CREATUREVIEWERINPUTMANAGER_H
#define CREATUREVIEWERINPUTMANAGER_H

#include "genelabcoreclasses.h"
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

        void initBulletOgre(BulletOgreEngine *btoEngine,Ogre::Camera *camera);

    private:

        void throwCube();
        Ogre::Camera *camera;
        BulletOgreEngine* btoEngine;
        int mNumEntitiesInstanced;

    };
}

#endif // CREATUREVIEWERINPUTMANAGER_H
