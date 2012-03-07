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

#ifndef BTSCENE_H
#define BTSCENE_H

#include <QObject>
#include <QVariant>

#include "genecraftcoreclasses.h"

class btVector3;
class btDynamicsWorld;
class btRigidBody;
class btCollisionShape;
class btDefaultMotionState;

namespace GeneCraftCore {


class btScene : public QObject
{

public:
    explicit btScene(btWorld* world, QVariant sceneData, QObject *parent = 0);
    ~btScene();

    virtual void setup();

    btVector3 getSpawnPosition();

    virtual void setBulletWorld(btDynamicsWorld* bulletWorld) {
        this->bulletWorld = bulletWorld;
    }

protected:
    QVariantMap data;
    btDynamicsWorld* bulletWorld;
    btWorld* world;
    QList<Spawn*> spawns;
    btDefaultMotionState* groundMotionState;
    btCollisionShape *collisionShape;
    btRigidBody *rigidBody;
    QList<Node<Linked*>*> shapes;
    float terrain[65*65];

    Terrain* terrainEngine;
    TerrainData* terrainData;
};

}

#endif // BTSCENE_H
