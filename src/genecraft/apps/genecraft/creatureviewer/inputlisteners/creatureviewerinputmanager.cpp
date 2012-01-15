/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "creatureviewerinputmanager.h"

// Qt
#include <QDebug>

#include "btoshapesfactory.h"
#include "entity.h"
#include "body/bone.h"
#include "body/treeshape.h"
#include "body/fixation.h"
#include "bullet/rigidbodyorigin.h"
#include "bulletogre/btoworld.h"

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

void CreatureViewerInputManager::setWorld(btWorld *world) {
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
        btoBox *box = new btoBox((btoWorld*)world, btoEngine,btVector3(1,1,1),transform, 1200.0);
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

    const btScalar RAY_LENGTH = 1000.0;

    // front of the camera (fps)
    // Ogre::Vector3 ogreRayFrom = camera->getPosition();
    // Ogre::Vector3 ogreRayTo = camera->getPosition() + camera->getDirection() * lenghtOfRay;
    // btVector3 rayFrom = btVector3(ogreRayFrom.x,ogreRayFrom.y,ogreRayFrom.z);
    // btVector3 rayTo = btVector3(ogreRayTo.x,ogreRayTo.y,ogreRayTo.z);

    // under mouse pointer
    OgreWidget *ogreWidget = btoEngine->getOgreEngine()->getOgreWidget("MainWidget"); // TODO pass this widget in constructor or not ?
    btScalar normalisedMouseX = mousePos.x() / (btScalar) ogreWidget->width();
    btScalar normalisedMouseY = mousePos.y() / (btScalar) ogreWidget->height();
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

        if(body) {

            //emit rigidBodySelected(body);

            //other exclusions ?
            if (!(body->isStaticObject() || body->isKinematicObject()))
            {
                if(body->getUserPointer() != NULL)
                {
                    RigidBodyOrigin* origin = static_cast<RigidBodyOrigin*>(body->getUserPointer());
                    if(origin != 0)
                    {
                        if(origin->getObject() != NULL)
                        {
                            switch((RigidBodyOrigin::RigidBodyType)origin->getType())
                            {
                            case RigidBodyOrigin::BONE:{

                                Bone *bone = dynamic_cast<Bone*>(origin->getObject());
                                emit sBoneSelected(bone);
                                emit sEntitySelected(bone->getEntity());

                            }
                            break;

                            case RigidBodyOrigin::FIXATION:{

                                Fixation *fix = dynamic_cast<Fixation*>(origin->getObject());
                                emit sFixationSelected(fix);
                                emit sEntitySelected(fix->getEntity());

                            }
                            break;

                            case RigidBodyOrigin::BASIC_SHAPE:{

                                //BasicShape *shape = dynamic_cast<BasicShape*>(reinterpret_cast<QObject*>(origin->getObject()));
                                //game->getOpenGLEngine()->getScene()->removeDrawableObject(shape);
                                //game->getBulletEngine()->getDynamicsWorld()->removeRigidBody(shape->getRigidBody());
                                //setInspector(new QLabel("BASIC_SHAPE"));

                            }
                            break;
                            }
                        }
                        else
                            qDebug() << Q_FUNC_INFO << "Object NULL";
                    }
                    else
                        qDebug() << Q_FUNC_INFO << "RigidBodyOrigin NULL";
                }
            }
        }
    }
}
