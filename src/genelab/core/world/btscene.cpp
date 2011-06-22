#include "btscene.h"


// Shapes
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "bulletogre/shapes/btosphere.h"
#include "bulletogre/shapes/btobox.h"
#include "bulletogre/shapes/btocylinder.h"
#include "btoshapesfactory.h"

namespace GeneLabCore {

    btScene::btScene(MainFactory* factory, QVariant sceneData, QObject *parent) :
        QObject(parent)
    {
        this->factory = factory;
        this->data = sceneData.toMap();
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
            rigidBody->setActivationState(DISABLE_DEACTIVATION);
            world->addRigidBody(rigidBody);
        }
    }
}
