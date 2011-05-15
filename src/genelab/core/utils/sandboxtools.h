#ifndef SANDBOXTOOLS_H
#define SANDBOXTOOLS_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QQueue>
#include <QDebug>
#include "classes.h"
#include "core/engine/bulletmanager.h"
#include "OgreBulletDynamicsRigidBody.h"

#include "OGRE/Ogre.h"
#include "core/engine/ogremanager.h"
#include "core/engine/engine.h"

namespace GeneLabCore {
class SandboxTools : public QObject
{
    Q_OBJECT
public:
    explicit SandboxTools(QObject *parent = 0);

    static OgreBulletDynamics::RigidBody *addBox(OgreManager* ogre, BulletManager *bulletMgr,
                                                 const Ogre::Vector3 &position,const Ogre::Vector3 &size, const Ogre::Quaternion &rotation = Ogre::Quaternion::IDENTITY);

    static OgreBulletDynamics::RigidBody *addSphere(OgreManager* ogre, BulletManager *bulletMgr,
                                                 const Ogre::Vector3 &position, double rayon);

    static OgreBulletDynamics::RigidBody *addCylinder(OgreManager* ogre, BulletManager *bulletMgr,
                                                 const Ogre::Vector3 &position, const Ogre::Vector3 &size);

private:
    static int mNumEntitiesInstanced;

signals:

public slots:

};
}
#endif // SANDBOXTOOLS_H
