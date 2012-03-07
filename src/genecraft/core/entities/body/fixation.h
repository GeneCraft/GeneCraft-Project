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

#ifndef FIXATION_H
#define FIXATION_H

#include <QObject>
#include <QList>
#include "genecraftcoreclasses.h"

class btRigidBody;
class btTransform;
class btTypedConstraint;

namespace GeneCraftCore {

    enum MotorFrom {fromDisabled, fromBrain, fromNormal, fromRandom};

    class Fixation : public QObject
    {

    public:

        // Constructor : Think to call setup method to add objects in the world
        Fixation(btShapesFactory *shapesFactory, btScalar radius, btTransform initTransform);

        // Surcharged constructor, called to create a fixation from a existant rigidbody
        Fixation(btShapesFactory *shapesFactory, Sphere* body, btScalar radius, btTransform localFixation, Bone *parentBone);

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

        // TO remove and attach children to a specific fixation
        void removeAndAttachChildrenTo(Fixation *parent);

        // To get the parent bone (return NULL it's a root fixation)
        Bone *getParentBone() { return parentBone; }

        // -----------
        // -- bones --
        // -----------
        QList<Bone *> &getBones()               { return bones; }

        // To create and attach a bone to the fixation
        Bone *addBone(btScalar yAxis, btScalar zAxis, btScalar boneRadius, btScalar boneLength, btScalar endFixRadius, const btVector3& lo, const btVector3 &up);

        // To attach a bone to the fixation
        void addBone(Bone *b, btScalar yAxis, btScalar zAxis, btVector3& lo, btVector3 &up);

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
        //btRigidBody *getRigidBody()             { return this->rigidBody; }
        void setSelected(bool isSelected);
        void setRadius(btScalar radius);
        btShapesFactory *getShapesFactory()     { return shapesFactory; }

        // -----------
        // -- tools --
        // -----------
        void fixeInTheAir();
        void unfixInTheAir();
        bool isFixedInTheAir(){ return airFixation != 0; }
        void setOutputsFrom(MotorFrom from);
        bool isInOnePiece();

        // The percent of penetration of bone into fixation (percent of fixation radius)
        static const btScalar PERCENT_BONE_INSIDE_FIX;

    protected:

        // Construction
        BulletEngine *bulletEngine;
        btShapesFactory *shapesFactory;
        btTransform localFixation;
        Sphere          *physObject;
        //TODO: Change to Link
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

        // parent bone
        Bone *parentBone;

    };
}
#endif // FIXATION_H
