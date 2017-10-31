/*
Copyright 2011, 2012 Aur√©lien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONTACTSENSOR_H
#define CONTACTSENSOR_H

#include "genecraftcoreclasses.h"
#include "sensor.h"
#include "LinearMath/btVector3.h"
#include <QVariant>
#include "btBulletCollisionCommon.h"

namespace GeneCraftCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * This sensor allows entities to know what fixation is in contact with static object.
 *
 * Unit : meter / step^2
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class ContactSensor : public Sensor
{
public:

    // To create
    ContactSensor(Fixation * fixation);

    // To create from serialization data
    ContactSensor(QVariant data, Fixation * fixation);

    // To indicate collision
    //void collideStaticObject(const btCollisionObject *object, btVector3 contactPoint);

    // To serialize
    virtual QVariant serialize();

    // To create empty sensor serialization data
    static QVariant generateEmpty();

    // To update brain inputs values
    void step();

private:

    //btWorld *world;
    BrainIn * collided, * inputY, * inputZ;
    btVector3 oldPosition, oldSpeed;


};

//struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback {

//        //! Constructor, pass whatever context you want to have available when processing contacts
//        /*! You may also want to set m_collisionFilterGroup and m_collisionFilterMask
//         *  (supplied by the superclass) for needsCollision() */
//        ContactSensorCallback(btRigidBody *tgtBody , ContactSensor *context /*, ... */)
//                : btCollisionWorld::ContactResultCallback(), body(tgtBody), ctxt(context) { }

//        btRigidBody *body; //!< The body the sensor is monitoring
//        ContactSensor *ctxt; //!< External information for contact processing

//        //! If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
//        /*! However, if you use a btCollisionObject for #body instead of a btRigidBody,
//         *  then this is unnecessaryócheckCollideWithOverride isn't available */
//        virtual bool needsCollision(btBroadphaseProxy* proxy) const {
//                // superclass will check m_collisionFilterGroup and m_collisionFilterMask
////                if(!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
////                        return false;
////                // if passed filters, may also want to avoid contacts between constraints
////                return body.checkCollideWithOverride(static_cast<btCollisionObject*>(proxy->m_clientObject));
//            return true;
//        }

//        //! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
//        virtual btScalar addSingleResult(btManifoldPoint& cp,
//                const btCollisionObject* colObj0,int partId0,int index0,
//                const btCollisionObject* colObj1,int partId1,int index1)
//        {
//                const btCollisionObject *object;

//                btVector3 pt; // will be set to point of collision relative to body
//                if(colObj0 == (btCollisionObject *) body) {
//                        pt = cp.m_localPointA;
//                        object = colObj0;

//                } else {
//                        //assert(colObj1==body && "body does not match either collision object");
//                        pt = cp.m_localPointB;
//                        object = colObj1;
//                }

//                // do stuff with the collision point
//                if(object->isStaticObject())
//                {
//                    ctxt->collideStaticObject(object,pt);
//                }

//                return 0; // not actually sure if return value is used for anything...?
//        }
//};
}

#endif // CONTACTSENSOR_H
