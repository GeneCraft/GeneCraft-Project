/*
Copyright 2011, 2012 Aur�lien Da Campo, Cyprien Huissoud

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

#include "btscene.h"

// Shapes
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "bullet/shapes/btsphere.h"
#include "bullet/shapes/btbox.h"
#include "bullet/shapes/btcylinder.h"
#include "btfactory.h"
#include "bullet/btworld.h"
#include "btshapesfactory.h"
#include "tools.h"


#include "spawn.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "LinearMath/btVector3.h"

#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

#include "terrain/terrain.h"

#include "btworldfactory.h"

namespace GeneCraftCore {

    double test[129*129];

    btScene::btScene(btWorld* world, QVariant sceneData, QObject *parent) :
        QObject(parent)
    {
        this->world = world;
        this->world->setScene(this);
        this->data = sceneData.toMap();
        QVariantList spawnData = data["spawns"].toList();

        foreach(QVariant v, spawnData) {
            this->spawns.append(new Spawn(v));
        }

        if(this->spawns.size() == 0) { // Prevent no spawn bug !
            this->spawns.append(new Spawn("position", btVector3(0, 10, 0)));
        }

        terrainEngine = (Terrain*)world->getFactory()->getEngineByName("Terrain");

        groundMotionState = NULL;
        rigidBody = NULL;
        collisionShape = NULL;
    }

    btScene::~btScene() {
        terrainEngine->removeTerrain(terrainData);
        qDeleteAll(spawns);
        spawns.clear();
        // The floor
        if(groundMotionState) {
            world->getBulletWorld()->removeRigidBody(rigidBody);
            delete rigidBody;
            delete collisionShape;
            delete groundMotionState;
            groundMotionState = NULL;
            rigidBody = NULL;
            collisionShape = NULL;
        }

        // and the shapes !!!
        qDeleteAll(shapes);
        shapes.clear();
    }

    void btScene::setup() {

        QVariantMap floor = data["floor"].toMap();

        QVariantList staticShapesList = data.value("shapes").toList();

        //floor["type"] = "randomBoxes";
        // Add the entry to the terrain engine
        terrainEngine->setShapesFactory(world->getShapesFactory());
        terrainData = terrainEngine->addTerrain(floor);
        terrainEngine->beforeStep();
        if(floor["type"].toString() == "flatland") {
            /*Testing*/
            //collisionShape = new btHeightfieldTerrainShape(129, 129, test, 1, -20, 20, 1, PHY_FLOAT, false);
            //collisionShape->setLocalScaling(btVector3(100.0/129., 1, 100.0/129));
            collisionShape = new btStaticPlaneShape(btVector3(0,1,0),0);
            btTransform worldTransform;
            worldTransform.setIdentity();
            //worldTransform.setOrigin(btVector3(-50, 0, -50));
            groundMotionState = new btDefaultMotionState(worldTransform);
            btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,collisionShape,btVector3(0,0,0));

            rigidBody = new btRigidBody(groundRigidBodyCI);
            rigidBody->setFriction(0.7);

            //rigidBody->setActivationState(DISABLE_DEACTIVATION);
            bulletWorld->addRigidBody(rigidBody);

        } else if(floor["type"].toString() == "boxfloor") {


            // STAIRS
           //btWorldFactory::createBoxesStairs(staticShapesList, 300, 300, btVector3(0, 0, 0), 10, 0.3, 0.5);
        }

        // Shapes
        if(data.contains("shapes")){


            foreach(QVariant shapeData, staticShapesList)
            {
                QVariantMap shapeMap = shapeData.toMap();
                QString type = shapeMap["type"].toString();

                if(type.compare("box") == 0) {

                    // position and rotation
                    btTransform transform; transform.setIdentity();
                    transform.setOrigin(btVector3(shapeMap.value("posX").toDouble(),shapeMap.value("posY").toDouble(),shapeMap.value("posZ").toDouble()));
                    transform.getBasis().setEulerZYX(shapeMap.value("eulerX").toDouble(),shapeMap.value("eulerY").toDouble(),shapeMap.value("eulerZ").toDouble());

                    // size
                    btVector3 size(shapeMap.value("sizeX").toDouble(),shapeMap.value("sizeY").toDouble(),shapeMap.value("sizeZ").toDouble());

                    // create the box
                    Node<Linked*>* box = (Node<Linked*>*)world->getShapesFactory()->createBox(size, transform, shapeMap["density"].toFloat());
                    box->setup();
                    shapes.append(box);

                }
                else if(type.compare("sphere") == 0) {

                    // position and rotation
                    btTransform transform; transform.setIdentity();
                    transform.setOrigin(btVector3(shapeMap.value("posX").toDouble(),shapeMap.value("posY").toDouble(),shapeMap.value("posZ").toDouble()));
                    transform.getBasis().setEulerZYX(shapeMap.value("eulerX").toDouble(),shapeMap.value("eulerY").toDouble(),shapeMap.value("eulerZ").toDouble());

                    // create the box
                    Node<Linked*>* sphere = (Node<Linked*>*) world->getShapesFactory()->createSphere(shapeMap.value("radius").toFloat(), transform, shapeMap["density"].toFloat());
                    sphere->setup();
                    shapes.append(sphere);
                }
                else if(type.compare("cylinder") == 0) {

                    // position and rotation
                    btTransform transform; transform.setIdentity();
                    transform.setOrigin(btVector3(shapeMap.value("posX").toDouble(),shapeMap.value("posY").toDouble(),shapeMap.value("posZ").toDouble()));
                    transform.getBasis().setEulerZYX(shapeMap.value("eulerX").toDouble(),shapeMap.value("eulerY").toDouble(),shapeMap.value("eulerZ").toDouble());

                    // create the box
                    Node<Linked*>* cylinder = (Node<Linked*>*) world->getShapesFactory()->createCylinder(shapeMap.value("radius").toFloat(), shapeMap.value("height").toFloat(), transform, shapeMap["density"].toFloat());
                    cylinder->setup();
                    shapes.append(cylinder);
                }
            }
        }
    }

    btVector3 btScene::getSpawnPosition() {
        int i = qrand()%spawns.size();
        return spawns.at(i)->getSpawnPosition();
    }
}
