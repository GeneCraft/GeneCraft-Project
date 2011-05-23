#include "creatureviewerinputmanager.h"
#include <QDebug>
#include "ogreengine.h"
#include "bulletengine.h"
#include "sandboxtools.h"
#include "OGRE/Ogre.h"
#include "Dynamics/OgreBulletDynamicsWorld.h"
#include "btobox.h"
#include "bulletogreengine.h"

namespace GeneLabCore {
CreatureViewerInputManager::CreatureViewerInputManager()
{
}

void CreatureViewerInputManager::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::RightButton)
        throwCube();
}
void CreatureViewerInputManager::mouseReleaseEvent(QMouseEvent * e){}
void CreatureViewerInputManager::mouseMoveEvent(QMouseEvent * e){}

void CreatureViewerInputManager::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_B :
            for(int i=0;i<100;i++)
                throwCube();
        break;
        case Qt::Key_P :
            btoEngine->getBulletEngine()->setPhysicsEnable(!btoEngine->getBulletEngine()->getPhysicsEnable());
        break;
        case Qt::Key_1 :
            camera->setPolygonMode(Ogre::PM_POINTS);
        break;
        case Qt::Key_2 :
            camera->setPolygonMode(Ogre::PM_WIREFRAME);
        break;
        case Qt::Key_3 :
            camera->setPolygonMode(Ogre::PM_SOLID);
        break;
    }
}

void CreatureViewerInputManager::keyReleaseEvent(QKeyEvent *e){}
void CreatureViewerInputManager::enterViewPortEvent(QEvent *e){}
void CreatureViewerInputManager::leaveViewPortEvent(QEvent *e){}

void CreatureViewerInputManager::initBulletOgre(BulletOgreEngine *btoEngine, Ogre::Camera *camera)
{
    this->camera = camera;
    this->btoEngine = btoEngine;
}

void CreatureViewerInputManager::throwCube()
{
    Ogre::Vector3 camPos = camera->getPosition();
    btoBox *box = new btoBox(btoEngine,btVector3(1,1,1),btVector3(camPos.x,camPos.y,camPos.z));
    box->setup();

    // apply impulse from the center of the box
    Ogre::Vector3 initialImpulse = camera->getDirection().normalisedCopy();
    initialImpulse *= 1/box->getRigidBody()->getInvMass() * 50;
    box->getRigidBody()->applyCentralImpulse(btVector3(initialImpulse.x,initialImpulse.y,initialImpulse.z));
}
}
