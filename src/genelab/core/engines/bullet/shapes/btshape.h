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
    virtual void setSelected(bool selected){};

    virtual void setup(){};

signals:

public slots:

protected:

    btWorld *world;
    btRigidBody *rigidBody;
    //btCollisionShape *collisionShape;

};

}

#endif // BTSHAPE_H
