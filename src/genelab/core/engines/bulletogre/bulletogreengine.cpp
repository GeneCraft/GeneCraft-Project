#include "bulletogreengine.h"

#include <QDebug>
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "bullet/bulletengine.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "Ogre.h"


namespace GeneLabCore {

    BulletOgreEngine::BulletOgreEngine(BulletEngine *btEngine, OgreEngine *ogreEngine)
    {
        this->btEngine = btEngine;
        this->ogreEngine = ogreEngine;
    }

    void BulletOgreEngine::addBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node)
    {
        bodies.append(OgreBody(rigidBody,entity,node));
    }

    void BulletOgreEngine::removeBody(btRigidBody *rigidBody, Ogre::Entity *entity, Ogre::SceneNode *node) {
        bodies.removeAll(OgreBody(rigidBody, entity, node));
    }
int nbStep;
void BulletOgreEngine::step()
{
    nbStep++;
    int sec = (nbStep/60)%60;
    int min = (nbStep/3600)%60;
    int hour = (nbStep/(3600*60));
    QString time = (hour?QString::number(hour) + "h ":"")
                  +(min?QString::number(min) + "m ":"")
                  +(sec?QString::number(sec) + "s -- ":" -- ")
                  +(QString::number(nbStep) + " steps");

    Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

    overlayManager.getOverlayElement("timeArea")->setCaption(time.toStdString());

    OgreBody body;
    QListIterator<OgreBody> it( bodies );
    while( it.hasNext() )
    {
        body = it.next();
        btTransform transform = body.rigidBody->getWorldTransform();
        if(transform.getOrigin().x() != transform.getOrigin().x())
            continue;

        body.node->setPosition(transform.getOrigin().x(),
                                transform.getOrigin().y(),
                                transform.getOrigin().z());

        body.node->setOrientation(transform.getRotation().w(),
                                   transform.getRotation().x(),
                                   transform.getRotation().y(),
                                   transform.getRotation().z());
    }
}
}
