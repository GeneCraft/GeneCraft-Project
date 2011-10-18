#ifndef SMELLSENSOR_H
#define SMELLSENSOR_H

#include "genecraftcoreclasses.h"
#include "sensor.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "bullet/rigidbodyorigin.h"

#include "btBulletCollisionCommon.h"

namespace GeneCraftCore {

class ContactSensorCallback;

class SmellSensor : public Sensor
{
public:
    SmellSensor(Fixation *fixation, QString typeName, SensorType type, RigidBodyOrigin::RigidBodyType smellType, btScalar radiusOfSmell);

    // To create from serialization data
    SmellSensor(QVariant data, RigidBodyOrigin::RigidBodyType smellType, Fixation * fixation);
    ~SmellSensor();

    // To serialize
    QVariant serialize();

    // To generate en empty sensor serialization data
    static QVariant generateEmpty(QString typeName, SensorType type, btScalar radiusOfSmell);

    // To update brain inputs values
    void step();

    virtual void objectSmelled(const btRigidBody *body);

    void contactCallBack(const btCollisionObject *body);

protected:

    RigidBodyOrigin::RigidBodyType smellType;
    btRigidBody * smellSphere;

    ContactSensorCallback *callback;
    btMotionState *motion;
    btCollisionShape *shape;

    btScalar radiusOfSmell;
    const btRigidBody *nearestBodySmelled;
    btScalar distanceOfNearestBodySmelled;

    BrainIn * intensityInput;

private:

    void createRigidBody(btScalar radiusOfSmell);

};

struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback {

        //! Constructor, pass whatever context you want to have available when processing contacts
        /*! You may also want to set m_collisionFilterGroup and m_collisionFilterMask
         *  (supplied by the superclass) for needsCollision() */
        ContactSensorCallback(btRigidBody *tgtBody , SmellSensor * context /*, ... */)
                : btCollisionWorld::ContactResultCallback(), body(tgtBody), ctxt(context) { }

        btRigidBody *body;
        SmellSensor *ctxt;

        // TODO
        //! If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
        /*! However, if you use a btCollisionObject for #body instead of a btRigidBody,
         *  then this is unnecessary—checkCollideWithOverride isn't available */
//        virtual bool needsCollision(btBroadphaseProxy* proxy) const {
//                // superclass will check m_collisionFilterGroup and m_collisionFilterMask
//                if(!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
//                        return false;
//                // if passed filters, may also want to avoid contacts between constraints
//                return body.checkCollideWithOverride(static_cast<btCollisionObject*>(proxy->m_clientObject));
//        }

        //! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
        virtual btScalar addSingleResult(btManifoldPoint& cp,
                const btCollisionObject* colObj0,int,int,
                const btCollisionObject* colObj1,int,int)
        {
                btVector3 pt; // will be set to point of collision relative to body
                if(colObj0==body) {
                    pt = cp.m_localPointA;

                    ctxt->contactCallBack(colObj1);

                } else {
                        assert(colObj1==body && "body does not match either collision object");
                        pt = cp.m_localPointB;

                    ctxt->contactCallBack(colObj0);
                }
                // do stuff with the collision point
                return 0; // not actually sure if return value is used for anything...?
        }
};

}

#endif // SMELLSENSOR_H
