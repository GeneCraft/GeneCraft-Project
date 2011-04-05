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
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
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
                                                 Ogre::Vector3 position, Ogre::Vector3 size_2);

private:
    static int mNumEntitiesInstanced;

signals:

public slots:

};

#endif // SANDBOXTOOLS_H
