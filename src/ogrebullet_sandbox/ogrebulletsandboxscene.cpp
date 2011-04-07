#include "ogrebulletsandboxscene.h"

OgreBulletSandBoxScene::OgreBulletSandBoxScene(GeneLabOgreBullet::BulletManager* bulletManager,
                                               GeneLabOgreBullet::OgreManager* ogreManager,
                                               QObject *parent) :
    OgreBulletScene(bulletManager,ogreManager,parent)
{
    //OGeneLabOgreBullet::OgreBulletScene(bulletManager,ogreManager)

   //this->bulletManager = bulletManager;
   //this->ogreManager = ogreManager;


    Ogre::SceneManager* sceneManager =  ogreManager->getOgreSceneManager();

    // FROM OGRE SCENE

    qDebug() << "Scene creation";
    //this->ogreRoot = ogreRoot;
    //this->sceneManager = sceneManager;
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
    Ogre::Entity* entNinja = sceneManager->createEntity("Ninja", "ninja.mesh");
    entNinja->setCastShadows(true);
    sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);







    // FROM BULLET MANAGER

    Ogre::Vector3 gravityVector(0,-9.81,0); // gravity vector for Bullet
    Ogre::AxisAlignedBox bounds(Ogre::Vector3 (-10000, -10000, -10000), //aligned box for Bullet
                               Ogre::Vector3 (10000,  10000,  10000));

    mMoveSpeed = 50;   // defined in ExampleFrameListener
    mNumEntitiesInstanced = 0; // how many shapes are created
    // Start Bullet
    mWorld = new OgreBulletDynamics::DynamicsWorld(sceneManager, bounds, gravityVector);

    // add Debug info display tool
    debugDrawer = new OgreBulletCollisions::DebugDrawer();
    debugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
    mWorld->setDebugDrawer(debugDrawer);
    mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers


    // TODO: Move in map !
    Ogre::SceneNode *node = sceneManager->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
    node->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));

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
                                                                                        mWorld);
    defaultPlaneBody->setStaticShape(Shape, 0.1, 0.8);// (shape, restitution, friction)
    // push the created objects to the deques
    mShapes.push_back(Shape);
    mBodies.push_back(defaultPlaneBody);

}
