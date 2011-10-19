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
   /**
    * @brief
    *
    */
   ~Bone();

   /** add bone and its end fixation in the world */
   /**
    * @brief
    *
    */
   void setup();
   /** To remove it without destructing entity */
   /**
    * @brief
    *
    */
   void remove();
   /** To remove only this bone (not recurcively) */
   /**
    * @brief
    *
    */
   void removeOnly();

   // -------------------
   // -- serialization --
   // -------------------
   /**
    * @brief
    *
    */
   QVariant serialize();
   /**
    * @brief
    *
    */
   static QVariant generateEmpty();

   // -------------------------
   // -- getters and setters --
   // -------------------------

   // parents
   /**
    * @brief
    *
    * @param ct
    */
   void setParentConstraint(btGeneric6DofConstraint *ct)   { this->parentCt = ct;          }
   /**
    * @brief
    *
    * @return btGeneric6DofConstraint *
    */
   btGeneric6DofConstraint * getParentConstraint()         { return parentCt;              }
   /**
    * @brief
    *
    * @param parentFix
    */
   void setParentFixation(Fixation *parentFix)             { this->parentFix = parentFix;  }
   /**
    * @brief
    *
    * @return Fixation *
    */
   Fixation *getParentFixation()                           { return parentFix;             }
   /**
    * @brief
    *
    * @return Fixation *
    */
   Fixation *getEndFixation()                              { return endFix;                }
   /**
    * @brief
    *
    * @return Entity *
    */
   Entity *getEntity()                                     { return entity;                }
   /**
    * @brief
    *
    * @param entity
    */
   void setEntity(Entity *entity);

   // motors
   /**
    * @brief
    *
    * @return RotationalMotorsEffector *
    */
   inline RotationalMotorsEffector *getRotationalMotorsEffector() { return motorsEffector; }
   /**
    * @brief
    *
    * @param data
    */
   inline void setMotorModifierData(QVariant data)         { this->motorModifierData = data; }

   // body & size
   /**
    * @brief
    *
    * @return btRigidBody *
    */
   btRigidBody* getRigidBody()                             { return rigidBody;             }
   /**
    * @brief
    *
    * @return btScalar
    */
   btScalar getLength()                                    { return body->getLength();     }
   /**
    * @brief
    *
    * @return btScalar
    */
   btScalar getRadius()                                    { return body->getRadius();     }
   /**
    * @brief
    *
    * @param radius
    * @param length
    */
   void setSize(btScalar radius, btScalar length);
   /**
    * @brief
    *
    * @param radius
    */
   void setEndFixationRadius(btScalar radius);

   // angular position
   /**
    * @brief
    *
    * @return btScalar
    */
   inline btScalar getYAxis() { return yAxis; }
   /**
    * @brief
    *
    * @return btScalar
    */
   inline btScalar getZAxis() { return zAxis; }
   /**
    * @brief
    *
    * @param yAxis
    */
   void setyAxis(btScalar yAxis);
   /**
    * @brief
    *
    * @param zAxis
    */
   void setZAxis(btScalar zAxis);
   /**
    * @brief
    *
    */
   void setToMinimalOuts();

   // tools
   /**
    * @brief
    *
    * @param selected
    */
   void setSelected(bool selected);

   // ------------
   // -- Motors --
   // ------------
   /**
    * @brief
    *
    */
   void setBrainMotors();
   /**
    * @brief
    *
    */
   void setRandomMotors();
   /**
    * @brief
    *
    */
   void disableMotors();
   /**
    * @brief
    *
    */
   void setNormalPositionMotors();
   /**
    * @brief
    *
    */
   void resetMotors();
   /**
    * @brief
    *
    * @param i
    */
   void connectMotor(int i);
   /**
    * @brief
    *
    * @param i
    */
   void disconnectMotor(int i);

protected:

   // Shape
   btScalar yAxis, zAxis; /**< TODO */
   btBone *body;             // Owner /**< TODO */
   btRigidBody *rigidBody; /**< TODO */
   RigidBodyOrigin *origin;  // Owner /**< TODO */
   Fixation *parentFix; /**< TODO */
   Fixation *endFix;         // Owner /**< TODO */

   // Modifier
   RotationalMotorsEffector *motorsEffector; // Owner /**< TODO */

   // Contraints
   btGeneric6DofConstraint *parentCt; // Owner /**< TODO */

   // MotorModifier data
   QVariant motorModifierData; /**< TODO */

   // Related Entity
   Entity *entity; /**< TODO */

   // Engine
   BulletEngine *bulletEngine; /**< TODO */

   // Shape factory
   btShapesFactory* shapesFactory; /**< TODO */

};

}
#endif // BONE_H
