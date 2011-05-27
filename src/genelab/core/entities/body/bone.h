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

   btRigidBody *rigidBody;
   RigidBodyOrigin *origin;
   Fixation *endFix;
   btGeneric6DofConstraint *parentCt;
   btGeneric6DofConstraint *endFixConstraint;

   btBone *body;

   btScalar radius;
   btScalar length;

   //OpenGLEngine *openGLEngine;
   OgreEngine* ogreManager; // AHAHAHAHAHAAHAHAHAHAHAH
   BulletEngine *bulletEngine;

   static BonePropertiesController *inspectorWidget;

   Entity *entity;
};

/*
    class Bone : public QObject
    {
        Q_OBJECT
    public:
        explicit Bone(QObject *parent = 0);
        Bone(float alpha_max, float beta_min, float beta_max, float r_min, float r_max, float length);
        ~Bone();

        float getLength();

        float rotationCapacity();
        float hingeCapacity();

        float getAlpha();
        float getBetaMin();

        //Fixe aticulation between angle_min and angle_max

        void contractInNormalPosition();

        Fixation* getFixation();

        void initOgreBullet(OgreManager* ogreManager, BulletManager *bulletManager);
        void setup();
        void attachToParentFixation(Fixation* parentFix);


        OgreBulletDynamics::RigidBody *getRigidBody();

        QString toString();

    signals:

    public slots:

    private:

        // Articulation properties
        float alpha_min, alpha_max;
        float beta_min, beta_max;
        float r_min, r_max;

        // Bone properties
        float boneRadius;
        float boneLength;
        float boneMass;
        OgreBulletDynamics::RigidBody *rigidBody;

        // End Fixation (totally limited on each axis)
        Fixation* end;

        // Six dof constraint
        OgreBulletDynamics::SixDofConstraint *parentSixDofConstraint;

        // Ogre and Bullet
        OgreManager* ogreManager;
        BulletManager *bulletManager;
    };
*/

}
#endif // BONE_H
