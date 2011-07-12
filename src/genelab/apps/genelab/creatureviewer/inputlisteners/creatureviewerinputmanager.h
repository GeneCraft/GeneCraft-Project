#ifndef CREATUREVIEWERINPUTMANAGER_H
#define CREATUREVIEWERINPUTMANAGER_H

#include "genelabcoreclasses.h"
#include "events/inspectorsinputmanager.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace GeneLabCore;

/**
 * (c) GeneLab 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Manage inputs into the creature viewer.
 * Emit rigidBodySelected when user click on a rigidBody into the scene.
 * Allow you to throw cube by right clicking.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo & Cyprien Huissoud
 */
class CreatureViewerInputManager : public InspectorsInputManager
{
    Q_OBJECT

public:

    CreatureViewerInputManager(BulletOgreEngine *btoEngine,Ogre::Camera *camera);

    // Events (called during beforeStep)
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void enterViewPortEvent(QEvent *e);
    void leaveViewPortEvent(QEvent *e);

    void setWorld(btoWorld* world);

signals:

    void rigidBodySelected(btRigidBody *rigidBody);

public slots:

private:

    void pickBody();
    void throwCube();
    Ogre::Camera *camera;
    BulletOgreEngine* btoEngine;
    int mNumEntitiesInstanced;
    QPoint mousePos;
    btoWorld* world;

    Bone *boneSelected;
    Fixation *fixSelected;

};


#endif // CREATUREVIEWERINPUTMANAGER_H
