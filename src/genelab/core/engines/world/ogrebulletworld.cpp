#include "ogrebulletworld.h"

#include <string.h>

// Qt
#include <QVariant>
#include <QTest>
#include <QDebug>

// Engines
#include "OGRE/Ogre.h"
#include "ogreengine.h"
#include "bulletengine.h"
#include "bulletogreengine.h"

// Shapes
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "btosphere.h"
#include "btobox.h"
#include "btocylinder.h"
#include "btoshapesfactory.h"

// Entity
#include "snakefamily.h"
#include "treeshape.h"
#include "fixation.h"
#include "spider/spider.h"

namespace GeneLabCore {

    OgreBulletWorld::OgreBulletWorld(BulletOgreEngine *btoEngine, QObject *parent) :
        World(parent)
    {
        this->btoEngine = btoEngine;
    }

    void OgreBulletWorld::setup() {

        OgreEngine* ogreEngine = btoEngine->getOgreEngine();
        BulletEngine* btEngine = btoEngine->getBulletEngine();

        // ---------------------
        // -- OGRE PROPERTIES --
        // ---------------------

        Ogre::SceneManager* sceneManager = ogreEngine->getOgreSceneManager();

        // skybox
        sceneManager->setSkyDome(true, "Examples/CloudySky");

        // lights
        sceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));
        sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

        Ogre::Light* pointLight = sceneManager->createLight("pointLight");
        pointLight->setType(Ogre::Light::LT_POINT);
        pointLight->setPosition(Ogre::Vector3(0, 150, 250));
        pointLight->setDiffuseColour(0.8, 0.8, 1.0);
        pointLight->setSpecularColour(0.8, 0.8, 1.0);

        Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
        directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
        directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, .25));
        directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, .25));
        directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));

        Ogre::Light* spotLight = sceneManager->createLight("spotLight");
        spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
        spotLight->setDiffuseColour(1.0, 1.0, 1.0);
        spotLight->setSpecularColour(1.0, 1.0, 1.0);
        spotLight->setDirection(-1, -1, 0);
        spotLight->setPosition(Ogre::Vector3(300, 300, 0));
        spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

        // -------------------------
        // -- List of Material :) --
        // -------------------------
        Ogre::ResourceManager::ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingleton().getResourceIterator();
        /*while (materialIterator.hasMoreElements())
        {
            QString matName = QString((static_cast<Ogre::MaterialPtr>(materialIterator.peekNextValue())).getPointer()->getName().c_str());

            if(matName.contains("Grass"))
                qDebug() << "****************************************************" ;

            qDebug() << matName;

            materialIterator.moveNext();
        }*/

        // --------------------------
        // -- Content of the scene --
        // --------------------------

        // Static Floor
        Ogre::Entity *ent;
        Ogre::Plane p;
        p.normal = Ogre::Vector3(0,1,0); p.d = 0;
        Ogre::MeshManager::getSingleton().createPlane("FloorPlane",
                                                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                p, 200000, 200000, 20, 20, true, 1, 9000, 9000,
                                                Ogre::Vector3::UNIT_Z);

        ent = sceneManager->createEntity("floor", "FloorPlane");
        ent->setMaterialName("Examples/GrassFloor");
        sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

        // physics
        btStaticPlaneShape *collisionShape = new btStaticPlaneShape(btVector3(0,1,0),0);
        btTransform worldTransform;
        worldTransform.setIdentity();
        btDefaultMotionState* groundMotionState = new btDefaultMotionState(worldTransform);
        btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,collisionShape,btVector3(0,0,0));

        btRigidBody *rigidBody = new btRigidBody(groundRigidBodyCI);
        rigidBody->setActivationState(DISABLE_DEACTIVATION);
        btEngine->getBulletDynamicsWorld()->addRigidBody(rigidBody);
        // rigidBody->setFriction(0.9);
        // rigidBody->setDamping(0.1,0.0);
        // rigidBody->setRestitution(0.5);

        // test bug memory
        //QTest::qWait(1000);
        //        for(int i = 0; i < 100; i++)
        //            ent = sceneManager->createEntity(QString(QString("cubic")+QString::number(i)).toStdString().c_str(), "cube.mesh");

        // ------------------
        // -- Basic shapes --
        // ------------------
        btoShapesFactory *shapesFactory = new btoShapesFactory(btoEngine);


        /*btTransform transformSphere; transformSphere.setIdentity();
        transformSphere.setOrigin(btVector3(0,5,0));
        btSphere *sphere = shapesFactory->createSphere(1,transformSphere);
        //btoSphere * sphere = new btoSphere(btoEngine,1,btVector3(0,5,0));
        sphere->setup();

        btTransform transformBox; transformBox.setIdentity();
        transformBox.setOrigin(btVector3(0,10,0));
        btBox * box = shapesFactory->createBox(btVector3(1,1,1),transformBox);
        //btoBox * box = new btoBox(btoEngine,btVector3(1,1,1),btVector3(0,10,0));
        box->setup();

        btTransform transformCylinder; transformCylinder.setIdentity();
        transformCylinder.setOrigin(btVector3(0,15,0));
        btCylinder * cylinder = shapesFactory->createCylinder(0.5,4,transformCylinder);
        //btoCylinder * cylinder = new btoCylinder(btoEngine,0.5,4,btVector3(0,15,0));
        cylinder->setup();*/

        // --------------
        // -- Entities --
        // --------------
        //no family entity
//        Fixation *f = new Fixation(shapesFactory,1,btVector3(0,1,1));
//        btTransform transform; transform.setIdentity();
//        f->addBone(transform,0.5,2,1,btVector3(0,0,0),btVector3(0,0,0));
//        f->addBone(transform,0.5,2,1,btVector3(0,0,0),btVector3(0,0,0));
//        f->setup();

        // Spider
        qDebug() << "Spider creation !";
        Spider *spider = new Spider();
        for(int i = 0; i < 1; i++) {
            for(int j = 0; j < 1; j++) {
                Entity* e = spider->createEntity(shapesFactory, btVector3(j*30,20,i*30));
                qDebug() << "spider setup !";
                e->setup();
            }
        }


        // Snake
        // Move into EntityFactory
        // Discussion about entity management to do...
        //    SnakeFamily * snakeFamily = new SnakeFamily(QVariant());
        //    OgreBulletEntity* snake = snakeFamily->createOgreBulletEntity();
        //    snake->init((OgreEngine*)factory->getEngines().find("Ogre").value(),
        //                (BulletEngine*)factory->getEngines().find("Bullet").value(),
        //                (BrainEngine*)factory->getEngines().find("Brain").value());

        //    snake->setup(); // position

        //    // attach the nose in the air
        //    btGeneric6DofConstraint *ctRoot = new btGeneric6DofConstraint(*snake->getShape()->getRoot()->getRigidBody(),btTransform(btQuaternion(),btVector3(0,0,0)),true);
        //    ctRoot->setAngularLowerLimit(btVector3(0,0,0));
        //    ctRoot->setAngularUpperLimit(btVector3(0,0,0));
        //    ((BulletEngine*)factory->getEngines().find("Bullet").value())->getBulletDynamicsWorld()->addConstraint(ctRoot);


//        // add collision detection to it
//        OgreBulletCollisions::CollisionShape *Shape;
//        Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0); // (normal vector, distance)
//        // a body is needed for the shape
//        OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody("BasePlane",
//                                                                                            bulletManager->getDynamicsWorld());
//        defaultPlaneBody->setStaticShape(Shape, 0.1, 0.8);// (shape, restitution, friction)

//        // push the created objects to the deques
//        mShapes.push_back(Shape);
//        mBodies.push_back(defaultPlaneBody);

//        // Ninja
//        int* a = new int[10000];
//        Ogre::Entity* entNinja = sceneManager->createEntity("Ninja", "ninja.mesh");
//        entNinja->setCastShadows(true);
//        sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);

        // Cube of cubes
    //    float size = 10.0f;
    //    for(int i=0;i<10;i++)
    //        for(int j=0;j<10;j++)
    //            for(int k=0;k<10;k++)
    //                SandboxTools::addBox(graphics,physics,Ogre::Vector3(i*size,k*size+size/2,j*size),Ogre::Vector3(size,size,size));

        // Six dof constraint
    //    OgreBulletDynamics::RigidBody *boxA = SandboxTools::addBox(ogreManager,bulletManager,Ogre::Vector3(0,10,0),Ogre::Vector3(1,1,1));
    //    OgreBulletDynamics::RigidBody *boxB = SandboxTools::addBox(ogreManager,bulletManager,Ogre::Vector3(4,10,0),Ogre::Vector3(1,1,1));
    //    OgreBulletDynamics::SixDofConstraint *ct = new OgreBulletDynamics::SixDofConstraint(boxA,boxB,Ogre::Vector3(1,0,0),Ogre::Quaternion(),Ogre::Vector3(-1,0,0),Ogre::Quaternion());
    //    bulletManager->getWorld()->addConstraint(ct);
    //    //g6DofCC->setConstraint((btGeneric6DofConstraint*) ct->getBulletTypedConstraint());


    //    btTransform transform;
    //    transform.setIdentity();
    //    transform.setOrigin(btVector3(0,3,0));
    //    transform.setRotation(btQuaternion(btVector3(0,1,0),30));
    //

        /* UNUSED !
        Ogre::Quaternion *q1 = new Ogre::Quaternion(Ogre::Radian(1.57),Ogre::Vector3(1,1,0));
        Ogre::Quaternion *q2 = new Ogre::Quaternion(Ogre::Radian(1.57),Ogre::Vector3(0,1,0));

        OgreBulletDynamics::RigidBody *boxA = SandboxTools::addBox(ogreManager,bulletManager,Ogre::Vector3(1,10,1),Ogre::Vector3(1,2,1),*q1);
        OgreBulletDynamics::RigidBody *boxB = SandboxTools::addBox(ogreManager,bulletManager,Ogre::Vector3(1,12,1),Ogre::Vector3(1,2,1),*q1);
        */

        // Snake
        //QMap<QString, QString> map;
        //map.insert("length","10");
        //map.insert("piecelength","10");

        // active motor
    //    for(int i=0;i<3;i++)
    //    {
    //        //btRotationalLimitMotor *motor = ctRoot->getRotationalLimitMotor(i);
    //        btRotationalLimitMotor *motor = ctRoot->getRotationalLimitMotor(0);

    //        motor->m_hiLimit = 0;
    //        motor->m_loLimit = 1;
    //        //motor->m_maxLimitForce = 100000;
    //        motor->m_enableMotor = true;
    //        motor->m_targetVelocity = 200;
    //        motor->m_maxMotorForce = 1000;
    //    }

    }
}


