#include "bulletogreengine.h"

#include <QDebug>
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "bulletengine.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "OGRE/Ogre.h"


namespace GeneLabCore {

    BulletOgreEngine::BulletOgreEngine(BulletEngine *btEngine, OgreEngine *ogreEngine)
    {
        this->btEngine = btEngine;
        this->ogreEngine = ogreEngine;
    }

    void BulletOgreEngine::addBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node)
    {
        bodies.append(new OgreBody(rigidBody,entity,node));
    }

    void BulletOgreEngine::step()
    {
        OgreBody *body;
        QListIterator<OgreBody *> it( bodies );
        qDebug() << bodies.length() << "rigid bodys !";
        while( it.hasNext() )
        {
            body = it.next();

            //qDebug() << "BulletOgreEngine::step(), adapte position and oriotation of object";


            btTransform transform = body->rigidBody->getWorldTransform();
            //if(transform.getOrigin().getX() != transform.getOrigin().getX()) // nan ?
            //    qDebug() << transform.getOrigin().getX() << transform.getOrigin().getY() << transform.getOrigin().getZ();

            body->node->setPosition(transform.getOrigin().x(),transform.getOrigin().y(),transform.getOrigin().z());
            body->node->setOrientation(transform.getRotation().w(),transform.getRotation().x(),transform.getRotation().y(),transform.getRotation().z());
        }
        //int bidon;
        //scanf("%d", &bidon);
    }
}
