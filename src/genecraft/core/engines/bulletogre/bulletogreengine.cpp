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

#include "bulletogreengine.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "bullet/bulletengine.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "Ogre.h"


namespace GeneCraftCore {

    OgreBody::OgreBody() {
        this->rigidBody = NULL;
        this->entity = NULL;
        this->node = NULL;
    }

    OgreBody::OgreBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node)
    {
        this->rigidBody = rigidBody;
        this->entity    = entity;
        this->node      = node;
    }

    OgreBody::OgreBody(const OgreBody &b) {
        this->rigidBody = b.rigidBody;
        this->entity    = b.entity;
        this->node      = b.node;
    }

    bool OgreBody::operator ==(OgreBody b) {
        return this->rigidBody == b.rigidBody
            && this->entity == b.entity
            && this->node == b.node;
    }



BulletOgreEngine::BulletOgreEngine(BulletEngine *btEngine, OgreEngine *ogreEngine)
{
    this->btEngine = btEngine;
    this->ogreEngine = ogreEngine;
    nbSteps = 0;
}

void BulletOgreEngine::addBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node)
{
    bodies.append(OgreBody(rigidBody,entity,node));
}

void BulletOgreEngine::removeBody(btRigidBody *rigidBody, Ogre::Entity *entity, Ogre::SceneNode *node) {
    bodies.removeAll(OgreBody(rigidBody, entity, node));
}

void BulletOgreEngine::step()
{
    nbSteps++;
    int sec = (nbSteps/60)%60;
    int min = (nbSteps/(60 * 60))%60;
    int hour = (nbSteps/(3600*60));
    QString time = (hour?QString::number(hour) + "h ":"")
                  +(min?QString::number(min) + "m ":"")
                  +(sec?QString::number(sec) + "s -- ":" -- ")
                  +(QString::number(nbSteps) + " steps");

    Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

    overlayManager.getOverlayElement("timeArea")->setCaption(time.toStdString());

    OgreBody body;
    QListIterator<OgreBody> it( bodies );
    while( it.hasNext() )
    {
        body = it.next();
        btTransform transform = body.rigidBody->getWorldTransform();

        body.node->setPosition(transform.getOrigin().x(),
                                transform.getOrigin().y(),
                                transform.getOrigin().z());

        body.node->setOrientation(transform.getRotation().w(),
                                   transform.getRotation().x(),
                                   transform.getRotation().y(),
                                   transform.getRotation().z());
    }
}

void BulletOgreEngine::clearAll(){
    bodies.clear();
    nbSteps = 0; // TODO not really clean to do this here...
}
OgreEngine *BulletOgreEngine::getOgreEngine()     { return this->ogreEngine;  }
BulletEngine *BulletOgreEngine::getBulletEngine() { return this->btEngine;    }

}
