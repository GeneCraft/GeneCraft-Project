#ifndef BTSHAPE_H
#define BTSHAPE_H

#include <QObject>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneLabCore {

class btShape : public QObject
{
public:
    explicit btShape(btWorld* world);
    ~btShape();
    btRigidBody * getRigidBody() { return rigidBody; }

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
