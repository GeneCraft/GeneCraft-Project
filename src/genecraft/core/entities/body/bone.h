#ifndef BONE_H
#define BONE_H

#include <QObject>
#include <QVariant>

#include "genecraftcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "bullet/shapes/btbone.h"

namespace GeneCraftCore {

class Bone : public QObject
{

public:

   // ---------------------------
   // -- constructor and setup --
   // ---------------------------
   Bone(btShapesFactory *shapesFactory, btScalar yAxis, btScalar zAxis, btScalar radius, btScalar lenght, btScalar endFixRadius, const btTransform &initTransform);
   ~Bone();

   /** add bone and its end fixation in the world */
   void setup();
   /** To remove it without destructing entity */
   void remove();
   /** To remove only this bone (not recurcively) */
   void removeOnly();

   // -------------------
   // -- serialization --
   // -------------------
   QVariant serialize();
   static QVariant generateEmpty();

   // -------------------------
   // -- getters and setters --
   // -------------------------

   // parents
   void setParentConstraint(btGeneric6DofConstraint *ct)   { this->parentCt = ct;          }
   btGeneric6DofConstraint * getParentConstraint()         { return parentCt;              }
   void setParentFixation(Fixation *parentFix)             { this->parentFix = parentFix;  }
   Fixation *getParentFixation()                           { return parentFix;             }
   Fixation *getEndFixation()                              { return endFix;                }
   Entity *getEntity()                                     { return entity;                }
   void setEntity(Entity *entity);

   // motors
   inline RotationalMotorsEffector *getRotationalMotorsEffector() { return motorsEffector; }
   inline void setMotorModifierData(QVariant data)         { this->motorModifierData = data; }

   // body & size
   btRigidBody* getRigidBody()                             { return rigidBody;             }
   btScalar getLength()                                    { return body->getLength();     }
   btScalar getRadius()                                    { return body->getRadius();     }
   void setSize(btScalar radius, btScalar length);
   void setEndFixationRadius(btScalar radius);

   // angular position
   inline btScalar getYAxis() { return yAxis; }
   inline btScalar getZAxis() { return zAxis; }
   void setyAxis(btScalar yAxis);
   void setZAxis(btScalar zAxis);
   void setToMinimalOuts();

   // tools
   void setSelected(bool selected);

   // ------------
   // -- Motors --
   // ------------
   void setBrainMotors();
   void setRandomMotors();
   void disableMotors();
   void setNormalPositionMotors();
   void resetMotors();
   void connectMotor(int i);
   void disconnectMotor(int i);

protected:

   // Shape
   btScalar yAxis, zAxis;
   btBone *body;             // Owner
   btRigidBody *rigidBody;
   RigidBodyOrigin *origin;  // Owner
   Fixation *parentFix;
   Fixation *endFix;         // Owner

   // Modifier
   RotationalMotorsEffector *motorsEffector; // Owner

   // Contraints
   btGeneric6DofConstraint *parentCt; // Owner

   // MotorModifier data
   QVariant motorModifierData;

   // Related Entity
   Entity *entity;

   // Engine
   BulletEngine *bulletEngine;

   // Shape factory
   btShapesFactory* shapesFactory;

};

}
#endif // BONE_H