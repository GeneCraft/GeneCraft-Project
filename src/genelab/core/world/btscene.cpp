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
            this->spawns.append(new Spawn(Spawn::Position, btVector3(0, 10, 0)));
        }
    }

    void btScene::setup() {

        QString type = data["type"].toString();
        if(type == "flatland") {
            btStaticPlaneShape *collisionShape = new btStaticPlaneShape(btVector3(0,1,0),0);
            btTransform worldTransform;
            worldTransform.setIdentity();
            btDefaultMotionState* groundMotionState = new btDefaultMotionState(worldTransform);
            btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,collisionShape,btVector3(0,0,0));

            btRigidBody *rigidBody = new btRigidBody(groundRigidBodyCI);
            //rigidBody->setActivationState(DISABLE_DEACTIVATION);
            bulletWorld->addRigidBody(rigidBody);
        }

        // Static box
        // ----------------
        // FIXME PROBLEME :
        //
        // Si on creer des btoBox ici, qu'est-ce qu'on fait dans btScene::setup (appelée plus haut) ?
        // btoBox gère déjà la partie Ogre et Bullet...
        //
        // Je propose de ne pas mettre d'héritage entre les entités btoScene - btScene,
        // btoBiome - btBiome et btoWorld - btWorld car elles sont vraiment spécifiques au programme final.
        //
        // Pas besoin de polymorphisme, en tout cas j'en ai pas trouvé une utilité, a moins que...
        //
        // Tu en penses quoi ?
        //
        if(data.contains("staticBoxes")){

            QVariantList boxesData = data.value("staticBoxes").toList();

            foreach(QVariant boxData, boxesData)
            {
                QVariantMap boxDataMap = boxData.toMap();

                // position and rotation
                btTransform transform; transform.setIdentity();
                transform.setOrigin(btVector3(boxDataMap.value("posX").toDouble(),boxDataMap.value("posY").toDouble(),boxDataMap.value("posZ").toDouble()));
                transform.getBasis().setEulerZYX(boxDataMap.value("euleurX").toDouble(),boxDataMap.value("euleurY").toDouble(),boxDataMap.value("euleurZ").toDouble());

                // size
                btVector3 size(boxDataMap.value("sizeX").toDouble(),boxDataMap.value("sizeY").toDouble(),boxDataMap.value("sizeZ").toDouble());

                // create the box
                btBox *box = world->getShapesFactory()->createBox(size,transform, 0.0);
                box->setup();
            }
        }
    }

    btVector3 btScene::getSpawnPosition() {
        int i = qrand()%spawns.size();
        return spawns.at(i)->getSpawnPosition();
    }
}
