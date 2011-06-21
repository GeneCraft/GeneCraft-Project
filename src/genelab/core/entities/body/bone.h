#ifndef BONE_H
#define BONE_H

#include <QObject>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include <QVariant>

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
   btScalar getLength()                                    { return length;                }
   btScalar getRadius()                                    { return radius;                }
   Fixation *getEndFixation()                              { return endFix;                }
   Entity *getEntity()                                     { return entity;                }
   void setEntity(Entity *entity);

   RotationalMotorsModifier *getRotationalMotorsModifier() { return motorsModifier;        }
   void setMotorModifierData(QVariant data) { this->motorModifierData = data; }
   BonePropertiesController *getInspectorWidget();
   static BonePropertiesController *getEmptyInspectorWidget();

   void setBrainMotors();
   void setRandomMotors();
   void disableMotors();
   void setNormalPositionMotors();
   void resetMotors();

   QVariant serialize();
   btScalar getYAxis() { return yAxis; }
   btScalar getZAxis() { return zAxis; }

   void setyAxis(btScalar yAxis);
   void setZAxis(btScalar zAxis);

   void setSelected(bool selected);

   void setSize(btScalar radius, btScalar length);

protected:

   // Shape
   btScalar yAxis, zAxis;
   btBone *body;
   btScalar radius;
   btScalar length;
   btRigidBody *rigidBody;
   RigidBodyOrigin *origin;
   Fixation *endFix;

   // Modifier
   RotationalMotorsModifier *motorsModifier;



   // Contraints
   btGeneric6DofConstraint *parentCt;
   btGeneric6DofConstraint *endFixConstraint;

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
