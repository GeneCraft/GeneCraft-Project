#ifndef FIXATION_H
#define FIXATION_H

#include <QObject>
#include <QList>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneLabCore {

    class Fixation : public QObject
    {
        Q_OBJECT

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
         * Used to create and attach a bone to the fixation
         */
        //Bone *addBone(const btQuaternion &localOrientation, btScalar boneRadius, btScalar boneLenght, btScalar endFixRadius, const btVector3 &lowerLimits, const btVector3 &upperLimits);
        Bone *addBone(btScalar yAxis, btScalar zAxis, btScalar boneRadius, btScalar boneLength, btScalar endFixRadius, const btVector3& lo, const btVector3 &up);

        /**
         * Used to add a sensor
         */
        void addSensor(Sensor * sensor);

        // GETTERS AND SETTERS
        QList<Bone *> &getBones()               { return bones; }
        QList<Sensor *> &getSensors()           { return sensors; }
        BulletEngine *getBulletEngine()         { return bulletEngine; }
        btScalar getRadius()                    { return radius; }
        void setEntity(Entity *entity);
        Entity *getEntity()                     { return entity; }
        btRigidBody *getRigidBody();
        FixationProperties *getInspectorWidget();
        static FixationProperties *getEmptyInspectorWidget();
        void setSelected(bool isSelected);
        void setRadius(btScalar radius);

        // TOOLS
        void fixeInTheAir();
        void unfixInTheAir();
        bool isFixedInTheAir(){ return airFixation != 0; }

        QVariant serialize();

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
        RigidBodyOrigin *origin;
        btScalar radius;
        btSphere *sphere;
        bool delegatedSetup;

        // Related entity
        Entity *entity;

        // Children
        QList<Bone *> bones;
        QList<Sensor *> sensors;
        //QList<Modifier *> modifiers;

        // Tools
        btTypedConstraint *airFixation;

        // Qt Render
        static FixationProperties *inspectorWidget;

        // parent bone
        Bone *parentBone;

    };
}
#endif // FIXATION_H
