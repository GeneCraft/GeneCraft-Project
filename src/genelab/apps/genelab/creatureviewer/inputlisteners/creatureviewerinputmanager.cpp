#include "creatureviewerinputmanager.h"

#include "families/spiderfamily.h"
#include "btoshapesfactory.h"
#include "entity.h"
#include "body/treeshape.h"
#include "body/fixation.h"

#include "world/btoworld.h"

// Qt
#include <QDebug>

// Ogre
#include "ogre/ogreengine.h"
#include "Ogre.h"
#include "ogre/ogrewidget.h"

// Bullet
#include "bullet/bulletengine.h"

// Bullet & Ogre
#include "bulletogre/shapes/btobox.h"
#include "bulletogre/bulletogreengine.h"

CreatureViewerInputManager::CreatureViewerInputManager(BulletOgreEngine *btoEngine,Ogre::Camera *camera) :
    camera(camera), btoEngine(btoEngine), world(NULL)
{
}

void CreatureViewerInputManager::setWorld(btoWorld *world) {
    this->world = world;
}

void CreatureViewerInputManager::mousePressEvent(QMouseEvent * e)
{
    // update mouse position (think to move in mouseMoveEvent if necessary...)
    mousePos.setX(e->pos().x());
    mousePos.setY(e->pos().y());

    // actions
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

void CreatureViewerInputManager::mouseReleaseEvent(QMouseEvent *){}
void CreatureViewerInputManager::mouseMoveEvent(QMouseEvent *){}

void CreatureViewerInputManager::keyPressEvent(QKeyEvent *e)
{
    // actions
    switch(e->key())
    {
    case Qt::Key_B :
        for(int i=0;i<10;i++)
            throwCube();
        break;
    case Qt::Key_P :
        btoEngine->getBulletEngine()->setPhysicsEnable(!btoEngine->getBulletEngine()->getPhysicsEnable());
        break;
    case Qt::Key_1 :
        //camera->setPolygonMode(Ogre::PM_POINTS);
        camera->setDebugDisplayEnabled(!camera->isDebugDisplayEnabled());
        break;
    case Qt::Key_2 :
        camera->setPolygonMode(Ogre::PM_WIREFRAME);
        break;
    case Qt::Key_3 :
        camera->setPolygonMode(Ogre::PM_SOLID);
        break;
    }
}

void CreatureViewerInputManager::keyReleaseEvent(QKeyEvent *){}
void CreatureViewerInputManager::enterViewPortEvent(QEvent *){}
void CreatureViewerInputManager::leaveViewPortEvent(QEvent *){}

void CreatureViewerInputManager::throwCube()
{

    // create a box in the camera position
    Ogre::Vector3 camPos = camera->getPosition();
    btTransform transform; transform.setIdentity();
    transform.setOrigin(btVector3(camPos.x,camPos.y,camPos.z));


    /*Spider f;
    btoShapesFactory *shapesFactory = new btoShapesFactory(btoEngine);

    Entity* e = f.createEntity(shapesFactory, transform.getOrigin());
    e->setup();
*/
    if(this->world) {
        btoBox *box = new btoBox(world, btoEngine,btVector3(1,1,1),transform, 800.0);
        box->setup();

        // apply impulse from the center of the box in direction of the camera
        Ogre::Vector3 initialImpulse = camera->getDirection().normalisedCopy();
        initialImpulse *= 1/box->getRigidBody()->getInvMass() * 50;
        box->getRigidBody()->applyCentralImpulse(btVector3(initialImpulse.x,initialImpulse.y,initialImpulse.z));
    }
}

void CreatureViewerInputManager::pickBody()
{
    if(!this->world)
        return;

    const float RAY_LENGTH = 1000.0;

    // front of the camera (fps)
    // Ogre::Vector3 ogreRayFrom = camera->getPosition();
    // Ogre::Vector3 ogreRayTo = camera->getPosition() + camera->getDirection() * lenghtOfRay;
    // btVector3 rayFrom = btVector3(ogreRayFrom.x,ogreRayFrom.y,ogreRayFrom.z);
    // btVector3 rayTo = btVector3(ogreRayTo.x,ogreRayTo.y,ogreRayTo.z);

    // under mouse pointer
    OgreWidget *ogreWidget = btoEngine->getOgreEngine()->getOgreWidget("MainWidget"); // TODO pass this widget in constructor or not ?
    float normalisedMouseX = mousePos.x() / (float) ogreWidget->width();
    float normalisedMouseY = mousePos.y() / (float) ogreWidget->height();
    Ogre::Ray ogreRay = camera->getCameraToViewportRay(normalisedMouseX,normalisedMouseY);
    Ogre::Vector3 ogreRayFrom = ogreRay.getOrigin();
    Ogre::Vector3 ogreRayTo = ogreRay.getOrigin() +  ogreRay.getDirection() * RAY_LENGTH;
    btVector3 rayFrom = btVector3(ogreRayFrom.x,ogreRayFrom.y,ogreRayFrom.z);
    btVector3 rayTo = btVector3(ogreRayTo.x,ogreRayTo.y,ogreRayTo.z);

    // find the closest rigidBody with raycast
    btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);
    world->getBulletWorld()->rayTest(rayFrom,rayTo,rayCallback);
    if (rayCallback.hasHit())
    {
        btRigidBody* body = btRigidBody::upcast(rayCallback.m_collisionObject);

        if(body)
            emit rigidBodySelected(body);
    }
}
