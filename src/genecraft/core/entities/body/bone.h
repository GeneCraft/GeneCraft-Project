/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

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

#ifndef BONE_H
#define BONE_H

#include <QObject>
#include <QJsonObject>

#include "genecraftcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "bullet/shapes/btbone.h"

namespace GeneCraftCore {

class Bone : public QObject
{

public:


  /**
   * @brief A bone, the physical preponderant part of a squelette of an entity. It's finished by a fixation
   where other bones can attach.
   *
   * @param shapesFactory the shape factory that allow the bone to create the needed physical/or graphical part
   * @param yAxis the yAxis position on the parent fixation
   * @param zAxis the xAxis position on the parent fixation
   * @param radius the radius of the bone (cylinder part)
   * @param lenght the length of the bone
   * @param endFixRadius the radis of the end fixation of the bone
   * @param initTransform the initial position of the muscle
   */
   Bone(btShapesFactory *shapesFactory, btScalar yAxis, btScalar zAxis, btScalar radius, btScalar lenght, btScalar endFixRadius, const btTransform &initTransform);
   /**
    * @brief destruct and free used ressources
    *
    */
   ~Bone();

   /**
    * @brief add bone and its end fixation in the world
    *
    */
   void setup();

   /**
    * @brief remove the bone without destructing entity
    *
    */
   void remove();
   /**
    * @brief remove only this bone (not recurcively) will not destroy child bones
    *
    */
   void removeOnly();

   /**
    * @brief create the basic genetic code for this bone
    *
    */
   QJsonObject serialize();
   /**
    * @brief create an empty piece of genetics for a bone
    *
    */
   static QJsonObject generateEmpty();

   // -------------------------
   // -- getters and setters --
   // -------------------------

   // parents
   /**
    * @brief set the parent constraint, the constraint between this bone and the parent fixation
    *
    * @param ct the constraint (bullet) between the bone and the parent fixation
    */
   void setParentConstraint(btGeneric6DofConstraint *ct)   { this->parentCt = ct;          }

   /**
    * @brief get the parent constraint, the constraint between this bone and the parent fixation
    *
    * @return btGeneric6DofConstraint * a pt to the constraint between the bone and the parent fixation
    */
   btGeneric6DofConstraint * getParentConstraint()         { return parentCt;              }

   /**
    * @brief set the pt to the parent fixation
    *
    * @param parentFix a pt to the parent Fixation*
    */
   void setParentFixation(Fixation *parentFix)             { this->parentFix = parentFix;  }
   /**
    * @brief get the pt to the parent fixation
    *
    * @return Fixation * a pt to the parent Fixation
    */
   Fixation *getParentFixation()                           { return parentFix;             }
   /**
    * @brief get the pt to the end fixation (the fixation at the end of the bone)
    *
    * @return Fixation * a pt to the Fixation at the end of the bone
    */
   Fixation *getEndFixation()                              { return endFix;                }
   /**
    * @brief get the entity where this bone belong
    *
    * @return Entity * a pt to the "parent" entity
    */
   Entity *getEntity()                                     { return entity;                }
   /**
    * @brief set the entity that contains this bone
    *
    * @param entity a pt to the "parent" entity
    */
   void setEntity(Entity *entity);

   // motors
   /**
    * @brief get the RotationalMotorsEffector between this bone and the parent fixation
    *
    * @return RotationalMotorsEffector * a pt to the RotationalMotorsEffector between this bone and the parent fixation
    */
   inline RotationalMotorsEffector *getRotationalMotorsEffector() { return motorsEffector; }
   /**
    * @brief the motor modification data, e.g. the genetic code for the brainoutput
    *
    * @param data genetic code for the brain needed data
    */
   inline void setMotorModifierData(QJsonObject data)         { this->motorModifierData = data; }

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
   QJsonObject motorModifierData; /**< TODO */

   // Related Entity
   Entity *entity; /**< TODO */

   // Engine
   BulletEngine *bulletEngine; /**< TODO */

   // Shape factory
   btShapesFactory* shapesFactory; /**< TODO */

};

}
#endif // BONE_H
