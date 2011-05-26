#include "creatureviewerinputmanager.h"
#include <QDebug>
#include "ogreengine.h"
#include "bulletengine.h"
//#include "sandboxtools.h"
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
    switch(e->button())
    {
    case Qt::RightButton :
        throwCube();
        break;

    case Qt::LeftButton :
        pickBody();
        break;

    default:
        break;
    }
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

    btTransform transform; transform.setIdentity();
    transform.setOrigin(btVector3(camPos.x,camPos.y,camPos.z));
    btoBox *box = new btoBox(btoEngine,btVector3(1,1,1),transform);
    box->setup();

    // apply impulse from the center of the box
    Ogre::Vector3 initialImpulse = camera->getDirection().normalisedCopy();
    initialImpulse *= 1/box->getRigidBody()->getInvMass() * 50;
    box->getRigidBody()->applyCentralImpulse(btVector3(initialImpulse.x,initialImpulse.y,initialImpulse.z));
}


void CreatureViewerInputManager::pickBody()
{
    bool m_ortho = false;
    btVector3 rayTo, rayFrom;

    if (m_ortho)
    {
        rayFrom = rayTo;
        rayFrom.setZ(-100.f);
    }
    else
    {
        Ogre::Vector3 ogreRayFrom = camera->getPosition();
        rayFrom = btVector3(ogreRayFrom.x,ogreRayFrom.y,ogreRayFrom.z);

        Ogre::Vector3 ogreRayTo = camera->getPosition() + camera->getDirection() * 1000;
        rayTo = btVector3(ogreRayTo.x,ogreRayTo.y,ogreRayTo.z);
    }

    btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);
    btoEngine->getBulletEngine()->getBulletDynamicsWorld()->rayTest(rayFrom,rayTo,rayCallback);

    if (rayCallback.hasHit())
    {
        btRigidBody* body = btRigidBody::upcast(rayCallback.m_collisionObject);

        if (body)
            emit rigidBodySelected(body);
    }
}

}
