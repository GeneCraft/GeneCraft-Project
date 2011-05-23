#ifndef BTSHAPE_H
#define BTSHAPE_H

#include <QObject>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace GeneLabCore;

class btShape : public QObject
{
    Q_OBJECT

public:
    explicit btShape(QObject *parent = 0);

    inline btRigidBody * getRigidBody() { return rigidBody; }
    //btCollisionShape *getCollisionShape(){ return collisionShape; }

    virtual void setup(){};

signals:

public slots:

protected:

    BulletEngine *btEngine;
    btRigidBody *rigidBody;
    //btCollisionShape *collisionShape;

};

#endif // BTSHAPE_H
