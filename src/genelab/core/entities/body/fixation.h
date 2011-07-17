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

        // Constructor : Think to call setup method to add objects in the world
        Fixation(btShapesFactory *shapesFactory, btScalar radius, btTransform initTransform);

        // Surcharged constructor, called to create a fixation from a existant rigidbody
        Fixation(btShapesFactory *shapesFactory, btRigidBody* body, btScalar radius, btTransform localFixation, Bone *parentBone);

        // Destuctor
        ~Fixation();

        // To serialize
        QVariant serialize();

        // To generate an empty serialized version
        static QVariant generateEmpty();

        // To set default parameters of fixation and add it into engines
        void setup();

        // To remove it without destructing entity
        void remove();

        // -----------
        // -- bones --
        // -----------
        QList<Bone *> &getBones()               { return bones; }

        // To create and attach a bone to the fixation
        Bone *addBone(btScalar yAxis, btScalar zAxis, btScalar boneRadius, btScalar boneLength, btScalar endFixRadius, const btVector3& lo, const btVector3 &up);

        // To delete manualy a bone
        void removeBone(Bone* bone);

        // -------------
        // -- sensors --
        // -------------
        QList<Sensor *> &getSensors()           { return sensors; }

        // To add a sensor
        void addSensor(Sensor * sensor);

        // To remove a sensor
        void removeSensor(Sensor * sensor);

        // ---------------
        // -- effectors --
        // ---------------
        QList<Effector *> &getEffectors()           { return effectors; }

        // To add an effector
        void addEffector(Effector * effector);

        // To remove an effector
        void removeEffector(Effector * effector);


        // -----------------------
        // -- getters / setters --
        // -----------------------
        BulletEngine *getBulletEngine()         { return bulletEngine; }
        btScalar getRadius()                    { return radius; }
        void setEntity(Entity *entity);
        Entity *getEntity()                     { return entity; }
        btRigidBody *getRigidBody()             { return this->rigidBody; }
        FixationPropertiesController *getInspectorWidget();
        static FixationPropertiesController *getEmptyInspectorWidget();
        void setSelected(bool isSelected);
        void setRadius(btScalar radius);
        btShapesFactory *getShapesFactory()     { return shapesFactory; }

        // -----------
        // -- tools --
        // -----------
        void fixeInTheAir();
        void unfixInTheAir();
        bool isFixedInTheAir(){ return airFixation != 0; }
        void setOutputsFrom(int from);
        bool isInOnePiece();

        // The percent of penetration of bone into fixation (percent of fixation radius)
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
        QList<Effector *> effectors; // Owner

        // Tools
        btTypedConstraint *airFixation; // Owner

        // Qt Render
        static FixationPropertiesController *inspectorWidget;

        // parent bone
        Bone *parentBone;

    };
}
#endif // FIXATION_H
