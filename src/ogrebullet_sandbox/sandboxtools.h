#ifndef SANDBOXTOOLS_H
#define SANDBOXTOOLS_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QQueue>
#include <QDebug>
#include "classes.h"
#include "physics/bulletmanager.h"
#include "OgreBulletDynamicsRigidBody.h"

#include "OGRE/Ogre.h"
#include "graphic/ogremanager.h"
#include "ogremanager.h"
#include "engine/engine.h"

class SandboxTools : public QObject
{
    Q_OBJECT
public:
    explicit SandboxTools(QObject *parent = 0);

    static OgreBulletDynamics::RigidBody *addBox(GeneLabOgreBullet::OgreManager* ogre, GeneLabOgreBullet::BulletManager *bulletMgr,
                                                 const Ogre::Vector3 &position,const Ogre::Vector3 &size, const Ogre::Quaternion &rotation = Ogre::Quaternion::IDENTITY);

    static OgreBulletDynamics::RigidBody *addSphere(GeneLabOgreBullet::OgreManager* ogre, GeneLabOgreBullet::BulletManager *bulletMgr,
                                                 const Ogre::Vector3 &position, double rayon);

    static OgreBulletDynamics::RigidBody *addCylinder(GeneLabOgreBullet::OgreManager* ogre, GeneLabOgreBullet::BulletManager *bulletMgr,
                                                 const Ogre::Vector3 &position, const Ogre::Vector3 &size);

private:
    static int mNumEntitiesInstanced;

signals:

public slots:

};

#endif // SANDBOXTOOLS_H
