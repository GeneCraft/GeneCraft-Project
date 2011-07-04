#ifndef BONE_H
#define BONE_H

#include <QObject>
#include <QVariant>

#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "bullet/shapes/btbone.h"

namespace GeneLabCore {

class Bone : public QObject
{
  Q_OBJECT

public:

   // ---------------------------
   // -- constructor and setup --
   // ---------------------------
   Bone(btShapesFactory *shapesFactory, btScalar yAxis, btScalar zAxis, btScalar radius, btScalar lenght, btScalar endFixRadius, const btTransform &initTransform);
   ~Bone();

   /** add bone and its end fixation in the world */
   void setup();

   // -------------------------
   // -- getters and setters --
   // -------------------------

   // parents
   void setParentConstraint(btGeneric6DofConstraint *ct)   { this->parentCt = ct;          }
   btGeneric6DofConstraint * getParentConstraint()         { return parentCt;              }
   Fixation *getEndFixation()                              { return endFix;                }
   Entity *getEntity()                                     { return entity;                }
   void setEntity(Entity *entity);

   // motors
   inline RotationalMotorsEffector *getRotationalMotorsEffector() { return motorsEffector; }
   inline void setMotorModifierData(QVariant data)         { this->motorModifierData = data; }

   // inspector
   BonePropertiesController *getInspectorWidget();
   static BonePropertiesController *getEmptyInspectorWidget();

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

   // -------------------
   // -- serialization --
   // -------------------
   QVariant serialize();

protected:

   // Shape
   btScalar yAxis, zAxis;
   btBone *body;             // Owner
   btRigidBody *rigidBody;
   RigidBodyOrigin *origin;  // Owner
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

   // Qt Render
   static BonePropertiesController *inspectorWidget;

};

}
#endif // BONE_H
