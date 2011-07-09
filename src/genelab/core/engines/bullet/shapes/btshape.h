#ifndef BTSHAPE_H
#define BTSHAPE_H

#include <QObject>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneLabCore {

class btShape : public QObject
{
    Q_OBJECT

public:
    explicit btShape(btWorld* world);
    ~btShape();
    btRigidBody * getRigidBody() { return rigidBody; }
    //btCollisionShape *getCollisionShape(){ return collisionShape; }

    // To get the world
    //btWorld *getWorld() { return world; }

    // What to do when shape is selected ?
    virtual void setSelected(bool){}

    // How to setup the shape in the world ?
    virtual void setup(){}

signals:

public slots:

protected:

    btWorld *world;
    btRigidBody *rigidBody;
    //btCollisionShape *collisionShape;

};

}

#endif // BTSHAPE_H
