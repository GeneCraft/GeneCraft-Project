#include "creatureviewerinputmanager.h"
#include <QDebug>
#include "ogremanager.h"
#include "bulletmanager.h"
#include "sandboxtools.h"
#include "OGRE/Ogre.h"

/// ---
/// AHAHA J'AI PAS TROUVE MIEUX POUR L'AUTO COMPLETION !!! HELP !
/// ---

#include "lib/ogrebullet-build/include/Dynamics/OgreBulletDynamicsWorld.h"

CreatureViewerInputManager::CreatureViewerInputManager()
{
}

void CreatureViewerInputManager::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::RightButton)
        throwCube();
}
void CreatureViewerInputManager::mouseReleaseEvent(QMouseEvent * e){}
void CreatureViewerInputManager::mouseMoveEvent(QMouseEvent * e){}

void CreatureViewerInputManager::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_B :
            for(int i=0;i<100;i++)
                throwCube();
        break;
        case Qt::Key_P :
            bulletManager->setPhysicsEnable(!bulletManager->getPhysicsEnable());
        break;
        case Qt::Key_1 :
            camera->setPolygonMode(Ogre::PM_POINTS );
        break;
        case Qt::Key_2 :
            camera->setPolygonMode(Ogre::PM_WIREFRAME);
        break;
        case Qt::Key_3 :
            camera->setPolygonMode(Ogre::PM_SOLID);
        break;
    }
}

void CreatureViewerInputManager::keyReleaseEvent(QKeyEvent *e){}
void CreatureViewerInputManager::enterViewPortEvent(QEvent *e){}
void CreatureViewerInputManager::leaveViewPortEvent(QEvent *e){}

void CreatureViewerInputManager::initOgreBullet(GeneLabOgreBullet::OgreManager* ogreManager,GeneLabOgreBullet::BulletManager *bulletManager, Ogre::Camera *camera)
{
    this->camera = camera;
    this->ogreManager = ogreManager;
    this->bulletManager = bulletManager;
}

void CreatureViewerInputManager::throwCube()
{
    OgreBulletDynamics::RigidBody * box = SandboxTools::addBox(ogreManager,bulletManager,camera->getPosition(),Ogre::Vector3(1,1,1));

    // apply impulse from the center of the box
    Ogre::Vector3 initialImpulse = camera->getDirection().normalisedCopy() * 40;
    box->getBulletRigidBody()->applyCentralImpulse(btVector3(initialImpulse.x,initialImpulse.y,initialImpulse.z));
}
