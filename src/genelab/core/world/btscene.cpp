#include "btscene.h"

// Shapes
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "bullet/shapes/btsphere.h"
#include "bullet/shapes/btbox.h"
#include "bullet/shapes/btcylinder.h"
#include "btfactory.h"
#include "world/btworld.h"
#include "factories/btshapesfactory.h"

namespace GeneLabCore {

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
    }

    btScene::~btScene() {
        qDeleteAll(spawns);
        spawns.clear();
    }

    void btScene::setup() {

        QVariantMap floor = data["floor"].toMap();

        if(floor["type"].toString() == "flatland") {
            btStaticPlaneShape *collisionShape = new btStaticPlaneShape(btVector3(0,1,0),0);
            btTransform worldTransform;
            worldTransform.setIdentity();
            btDefaultMotionState* groundMotionState = new btDefaultMotionState(worldTransform);
            btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,collisionShape,btVector3(0,0,0));

            btRigidBody *rigidBody = new btRigidBody(groundRigidBodyCI);
            rigidBody->setFriction(0.7);

            //rigidBody->setActivationState(DISABLE_DEACTIVATION);
            bulletWorld->addRigidBody(rigidBody);
        }

        // Shapes
        if(data.contains("shapes")){

            QVariantList staticShapesList = data.value("shapes").toList();

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
                    btBox *box = world->getShapesFactory()->createBox(size, transform, shapeMap["density"].toFloat());
                    box->setup();

                }
                else if(type.compare("sphere") == 0) {

                    // position and rotation
                    btTransform transform; transform.setIdentity();
                    transform.setOrigin(btVector3(shapeMap.value("posX").toDouble(),shapeMap.value("posY").toDouble(),shapeMap.value("posZ").toDouble()));
                    transform.getBasis().setEulerZYX(shapeMap.value("eulerX").toDouble(),shapeMap.value("eulerY").toDouble(),shapeMap.value("eulerZ").toDouble());

                    // create the box
                    btSphere *shere = world->getShapesFactory()->createSphere(shapeMap.value("radius").toFloat(), transform, shapeMap["density"].toFloat());
                    shere->setup();
                }
                else if(type.compare("cylinder") == 0) {

                    // position and rotation
                    btTransform transform; transform.setIdentity();
                    transform.setOrigin(btVector3(shapeMap.value("posX").toDouble(),shapeMap.value("posY").toDouble(),shapeMap.value("posZ").toDouble()));
                    transform.getBasis().setEulerZYX(shapeMap.value("eulerX").toDouble(),shapeMap.value("eulerY").toDouble(),shapeMap.value("eulerZ").toDouble());

                    // create the box
                    btCylinder *cylinder = world->getShapesFactory()->createCylinder(shapeMap.value("radius").toFloat(), shapeMap.value("height").toFloat(), transform, shapeMap["density"].toFloat());
                    cylinder->setup();
                }
            }
        }
    }

    btVector3 btScene::getSpawnPosition() {
        int i = qrand()%spawns.size();
        return spawns.at(i)->getSpawnPosition();
    }
}
