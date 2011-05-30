#ifndef BONE_H
#define BONE_H

#include <QObject>
#include <QDebug>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"

namespace GeneLabCore {

class Bone : public QObject
{
  Q_OBJECT

public:

   Bone(btShapesFactory *shapesFactory, btScalar radius, btScalar lenght, btScalar endFixRadius, const btTransform &initTransform);
   ~Bone();

   void setup();

   inline btRigidBody* getRigidBody()                             { return rigidBody;             }
   inline void setParentConstraint(btGeneric6DofConstraint *ct)   { this->parentCt = ct;          }
   inline btGeneric6DofConstraint * getParentConstraint()         { return parentCt;              }
   inline btScalar getLength()                                    { return length;                }
   inline Fixation *getEndFixation()                              { return endFix;                }
   //inline void setSelected(bool isSelected)                       { body->setSelected(isSelected);}
   inline Entity *getEntity()                                     { return entity;                }
   void setEntity(Entity *entity);

   BonePropertiesController *getInspectorWidget();

   void setRandomMotors();
   void resetMotors();

protected:

   // Shape
   btRigidBody *rigidBody;
   RigidBodyOrigin *origin;
   Fixation *endFix;
   btGeneric6DofConstraint *parentCt;
   btGeneric6DofConstraint *endFixConstraint;
   btBone *body;
   btScalar radius;
   btScalar length;

   // Modifier
   RotationalMotorsModifier *motorsModifier;

   // Related Entity
   Entity *entity;

   // Engine
   BulletEngine *bulletEngine;

   // Qt Render
   static BonePropertiesController *inspectorWidget;

};

}
#endif // BONE_H
