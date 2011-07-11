#ifndef FIXATION_H
#define FIXATION_H

#include <QObject>
#include <QList>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneLabCore {

    class Fixation : public QObject
    {

    public:

        /**
         * Constructor.
         *
         * Think to call setup method to add objects in the world.
         */
        Fixation(btShapesFactory *shapesFactory, btScalar radius, btTransform initTransform);

        /**
          * Surcharged constructor, called to create a fixation from a existant rigidbody
          */
        Fixation(btShapesFactory *shapesFactory, btRigidBody* body, btScalar radius, btTransform localFixation, Bone *parentBone);
        ~Fixation();

        /**
         * Used to set default parameters of fixation and add it into engines
         */
        void setup();
        /**
          * To remove it without destructing entity
          */
        void remove();

        /**
         * Used to create and attach a bone to the fixation
         */
        //Bone *addBone(const btQuaternion &localOrientation, btScalar boneRadius, btScalar boneLenght, btScalar endFixRadius, const btVector3 &lowerLimits, const btVector3 &upperLimits);
        Bone *addBone(btScalar yAxis, btScalar zAxis, btScalar boneRadius, btScalar boneLength, btScalar endFixRadius, const btVector3& lo, const btVector3 &up);

        /**
          * To delete manualy a bone
          */
        void removeBone(Bone* bone);

        /**
         * Used to add a sensor
         */
        void addSensor(Sensor * sensor);

        /**
         * Used to remove a sensor
         */
        void removeSensor(Sensor * sensor);

        // GETTERS AND SETTERS
        QList<Bone *> &getBones()               { return bones; }
        QList<Sensor *> &getSensors()           { return sensors; }
        BulletEngine *getBulletEngine()         { return bulletEngine; }
        btScalar getRadius()                    { return radius; }
        void setEntity(Entity *entity);
        Entity *getEntity()                     { return entity; }
        btRigidBody *getRigidBody()             { return this->rigidBody; }
        FixationProperties *getInspectorWidget();
        static FixationProperties *getEmptyInspectorWidget();
        void setSelected(bool isSelected);
        void setRadius(btScalar radius);

        // TOOLS
        void fixeInTheAir();
        void unfixInTheAir();
        bool isFixedInTheAir(){ return airFixation != 0; }

        QVariant serialize();

        // To get the sphere world
        btShapesFactory *getShapesFactory() { return shapesFactory; }

        /**
         * The percent of penetration of bone into fixation (percent of fixation radius)
         */
        static const btScalar PERCENT_BONE_INSIDE_FIX;

    protected:

        // Construction
        BulletEngine *bulletEngine;
        btShapesFactory *shapesFactory;
        btTransform localFixation;
        btRigidBody *rigidBody;
        RigidBodyOrigin *origin; // Owner
        btScalar radius;
        btSphere *sphere; // Owner
        bool delegatedSetup;

        // Related entity
        Entity *entity;

        // Children
        QList<Bone *> bones; // Owner
        QList<Sensor *> sensors; // Owner
        //QList<Effector *> effector;

        // Tools
        btTypedConstraint *airFixation; // Owner

        // Qt Render
        static FixationProperties *inspectorWidget;

        // parent bone
        Bone *parentBone;

    };
}
#endif // FIXATION_H
