// Ogre
#include "OGRE/Ogre.h"

// OgreBullet
#include "OgreBulletDynamicsConstraint.h"
#include "Dynamics/Constraints/OgreBulletDynamics6DofConstraint.h"

// Core
#include "entity/entity.h"

// GeneLab
#include "graphic/ogremanager.h"
#include "graphic/ogrewidget.h"
#include "graphic/ogrescene.h"
#include "physics/bulletmanager.h"
#include "simulation/simulationmanager.h"
#include "simulation/ogrebulletsimulationmanager.h"
#include "factory/jsonloader.h"
#include "eventmanager.h"
#include "sample/snakefamily.h"
#include "entity/struct/treeshape.h"
#include "entity/struct/fixation.h"
#include "ogrebulletentity.h"
#include "ogrescene.h"

#include "ogrebulletsandboxscene.h"
#include "sandboxtools.h"
#include "generic6dofconstraintcontroller.h"
#include "sample/snakefamily.h"
#include "OgreBulletCollisions.h"

OgreBulletSandBoxScene::OgreBulletSandBoxScene(GeneLabOgreBullet::BulletManager* bulletManager,
                                               GeneLabOgreBullet::OgreManager* ogreManager,
                                               QObject *parent) :
    OgreBulletScene(bulletManager,ogreManager,parent)
{

}

void OgreBulletSandBoxScene::init()
{
    // ---------------------
    // -- OGRE PROPERTIES --
    // ---------------------

    Ogre::SceneManager* sceneManager = ogreManager->getOgreSceneManager();

    // skybox
    sceneManager->setSkyBox(true, "Examples/SpaceSkyBox");

    // lights
    sceneManager->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));
    sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    Ogre::Light* pointLight = sceneManager->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 150, 250));
    pointLight->setDiffuseColour(1.0, 0.0, 0.0);
    pointLight->setSpecularColour(1.0, 0.0, 0.0);

    Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));

    Ogre::Light* spotLight = sceneManager->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setDirection(-1, -1, 0);
    spotLight->setPosition(Ogre::Vector3(300, 300, 0));
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    // --------------------------
    // -- Content of the scene --
    // --------------------------

    // Define a floor plane mesh
    Ogre::Entity *ent;
    Ogre::Plane p;
    p.normal = Ogre::Vector3(0,1,0); p.d = 0;
    Ogre::MeshManager::getSingleton().createPlane("FloorPlane",
                                            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                            p, 200000, 200000, 20, 20, true, 1, 9000, 9000,
                                            Ogre::Vector3::UNIT_Z);
    // Create an entity (the floor)
    ent = sceneManager->createEntity("floor", "FloorPlane");
    ent->setMaterialName("Examples/BumpyMetal");
    sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

    // add collision detection to it
    OgreBulletCollisions::CollisionShape *Shape;
    Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0); // (normal vector, distance)
    // a body is needed for the shape
    OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody("BasePlane",
                                                                                        bulletManager->getWorld());
    defaultPlaneBody->setStaticShape(Shape, 0.1, 0.8);// (shape, restitution, friction)

    // push the created objects to the deques
    mShapes.push_back(Shape);
    mBodies.push_back(defaultPlaneBody);

    // Ninja
//    Ogre::Entity* entNinja = sceneManager->createEntity("Ninja", "ninja.mesh");
//    entNinja->setCastShadows(true);
//    sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);

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

    GeneLabOgreBullet::SnakeFamily * snakeFamily = new GeneLabOgreBullet::SnakeFamily(QVariant());
    GeneLabOgreBullet::OgreBulletEntity* snake = snakeFamily->createOgreBulletEntity();
    snake->initOgreBullet(ogreManager,bulletManager);
    snake->setup(); // position

    // attach the nose in the air
    btGeneric6DofConstraint *ctRoot = new btGeneric6DofConstraint(*snake->getShape()->getRoot()->getRigidBody()->getBulletRigidBody(),btTransform(btQuaternion(),btVector3(0,0,0)),true);
    ctRoot->setAngularLowerLimit(btVector3(0,0,0));
    ctRoot->setAngularUpperLimit(btVector3(0,0,0));
    bulletManager->getWorld()->getBulletDynamicsWorld()->addConstraint(ctRoot);

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
