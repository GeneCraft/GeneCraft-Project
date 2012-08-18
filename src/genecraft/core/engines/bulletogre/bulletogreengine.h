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

#ifndef BULLETOGREENGINE_H
#define BULLETOGREENGINE_H

#include "genecraftcoreclasses.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "engine.h"
#include "lib/ogre/include/OGRE/Ogre.h"

namespace GeneCraftCore {

/**
 * Class used to links ogre objects to bullet objects
 */
class OgreBody
{
public:

    OgreBody();
    OgreBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node);

    OgreBody(const OgreBody &b);

    bool operator ==(OgreBody b);

    btRigidBody *rigidBody;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;
};


class BulletOgreEngine : public Engine
{
public:

    BulletOgreEngine(BulletEngine *btEngine, OgreEngine *ogreEngine);
    void addBody(btRigidBody * rigidBody, Ogre::Entity *entity, Ogre::SceneNode *node);
    void removeBody(btRigidBody * rigidBody, Ogre::Entity* entity, Ogre::SceneNode * node);
    OgreEngine *getOgreEngine();
    BulletEngine *getBulletEngine();

    void clearAll();

    void step();

private:

    BulletEngine *btEngine;
    OgreEngine *ogreEngine;
    QList<OgreBody> bodies;

    int nbSteps;
};
}
#endif // BULLETOGREENGINE_H
