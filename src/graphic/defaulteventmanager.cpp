#include "defaulteventmanager.h"

using namespace Ogre;

DefaultEventManager::DefaultEventManager(GeneLabOgreBullet::OgreManager *ogre, OgreBulletDynamics::DynamicsWorld *mWorld, QObject *parent) :
        GeneLabCore::Engine(parent)
{
    this->ogre = ogre;
    mOgreRoot = ogre->getOgreRoot();
    mSceneMgr = ogre->getOgreSceneManager();

    this->mWorld = mWorld;

    mNumEntitiesInstanced = 0;
}

void DefaultEventManager::mousePressEvent(QMouseEvent * e)
{
    eventsQueue.enqueue(e);
}

void DefaultEventManager::mouseReleaseEvent(QMouseEvent * e)
{
    eventsQueue.enqueue(e);
}

void DefaultEventManager::mouseMoveEvent(QMouseEvent * e)
{
    eventsQueue.enqueue(e);
}

void DefaultEventManager::keyPressEvent(QKeyEvent *e)
{
    eventsQueue.enqueue(e);
}

void DefaultEventManager::keyReleaseEvent(QKeyEvent *e)
{
    eventsQueue.enqueue(e);
}

void DefaultEventManager::enterViewPortEvent (QEvent *e)
{
    eventsQueue.enqueue(e);
}

void DefaultEventManager::leaveViewPortEvent (QEvent *e)
{
    eventsQueue.enqueue(e);
}

// Engine
void DefaultEventManager::beforeStep(){

    while(!eventsQueue.empty())
    {
        QEvent *e = eventsQueue.dequeue();QMouseEvent *me; QKeyEvent *ke;

        switch(e->type())
        {
        case QEvent::MouseButtonPress :

            me = (QMouseEvent*) e;
            if(me->button() == Qt::RightButton)
                throwCube();

            break;
        case QEvent::KeyRelease :

            ke = (QKeyEvent*) e;

            switch(ke->key())
            {
                case Qt::Key_B :
                    for(int i=0;i<100;i++)
                        throwCube();
                break;
            }

            break;
        }
    }
}


void DefaultEventManager::throwCube()
{

    qDebug() << "adding a box !";
    Vector3 size = Vector3::ZERO;	// size of the box
    // starting position of the box
    Camera* mCamera = this->ogre->getOgreSceneManager()->getCamera("first");
    Vector3 position = (mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 10);

    // create an ordinary, Ogre mesh with texture
    Entity *entity = mSceneMgr->createEntity(
            "Box" + StringConverter::toString(mNumEntitiesInstanced),
            "cube.mesh");

    entity->setCastShadows(true);


    qDebug() << "entity created";

    // we need the bounding box of the box to be able to set the size of the Bullet-box
    AxisAlignedBox boundingB = entity->getBoundingBox();
    size = boundingB.getSize(); size /= 2.0f; // only the half needed
    size *= 0.95f;	// Bullet margin is a bit bigger so we need a smaller size
    // (Bullet 2.76 Physics SDK Manual page 18)
    entity->setMaterialName("Examples/Rockwall");
    entity->setCastShadows(true);


    qDebug() << "material too";

    SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(entity);
    node->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us
    size *= 0.05f;						// don't forget to scale down the Bullet-box too


    qDebug() << "attached !";
    // after that create the Bullet shape with the calculated size
    OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);
    // and the Bullet rigid body
    OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
            "defaultBoxRigid" + StringConverter::toString(mNumEntitiesInstanced),
            mWorld);
    defaultBody->setShape(	node,
                                sceneBoxShape,
                                0.6f,			// dynamic body restitution
                                0.6f,			// dynamic body friction
                                1.0f, 			// dynamic bodymass
                                position,		// starting position of the box
                                Quaternion(0,0,0,1));// orientation of the box
    mNumEntitiesInstanced++;

    qDebug() << "shape ok";
    defaultBody->setLinearVelocity(
            mCamera->getDerivedDirection().normalisedCopy() * 7.0f ); // shooting speed




    // apply impulse from the center of the box
    Vector3 initialImpulse = mCamera->getDirection().normalisedCopy() * 200;
    defaultBody->getBulletRigidBody()->applyCentralImpulse(btVector3(initialImpulse.x,initialImpulse.y,initialImpulse.z));



    qDebug() << "velocity too";
    // push the created objects to the dequese
    //mShapes.push_back(sceneBoxShape);
    //mBodies.push_back(defaultBody);

    qDebug() << "end";
}

void DefaultEventManager::step(){
}


void DefaultEventManager::afterStep(){

}
