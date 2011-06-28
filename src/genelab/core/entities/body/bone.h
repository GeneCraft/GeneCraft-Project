#ifndef BONE_H
#define BONE_H

#include <QObject>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include <QVariant>
#include "bullet/shapes/btbone.h"

namespace GeneLabCore {

class Bone : public QObject
{
  Q_OBJECT

public:

   Bone(btShapesFactory *shapesFactory, btScalar yAxis, btScalar zAxis, btScalar radius, btScalar lenght, btScalar endFixRadius, const btTransform &initTransform);
   ~Bone();

   void setup();

   btRigidBody* getRigidBody()                             { return rigidBody;             }
   void setParentConstraint(btGeneric6DofConstraint *ct)   { this->parentCt = ct;          }
   btGeneric6DofConstraint * getParentConstraint()         { return parentCt;              }
   btScalar getLength()                                    { return body->getLength();     }
   btScalar getRadius()                                    { return body->getRadius();     }

   Fixation *getEndFixation()                              { return endFix;                }
   Entity *getEntity()                                     { return entity;                }
   void setEntity(Entity *entity);

   inline RotationalMotorsModifier *getRotationalMotorsEffector() { return motorsEffector; }
   inline void setMotorModifierData(QVariant data) { this->motorModifierData = data; }
   BonePropertiesController *getInspectorWidget();
   static BonePropertiesController *getEmptyInspectorWidget();

   void setBrainMotors();
   void setRandomMotors();
   void disableMotors();
   void setNormalPositionMotors();
   void resetMotors();

   QVariant serialize();
   inline btScalar getYAxis() { return yAxis; }
   inline btScalar getZAxis() { return zAxis; }

   void setyAxis(btScalar yAxis);
   void setZAxis(btScalar zAxis);

   void setSelected(bool selected);

   void setSize(btScalar radius, btScalar length);
   void setEndFixationRadius(btScalar radius);

   void connectMotor(int i);
   void disconnectMotor(int i);

protected:

   // Shape
   btScalar yAxis, zAxis;
   btBone *body;             // Owner
   btRigidBody *rigidBody;
   RigidBodyOrigin *origin;  // Owner
   Fixation *endFix;         // Owner

   // Modifier
   RotationalMotorsModifier *motorsEffector; // Owner

   // Contraints
   btGeneric6DofConstraint *parentCt;          // Owner

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
