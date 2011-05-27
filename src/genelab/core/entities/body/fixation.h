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
          *
          * Surchrged constructor, called to create a fixation from a existant rigidbody
          */
        Fixation(btShapesFactory *shapesFactory, btRigidBody* body, btScalar radius, btTransform localFixation);
        ~Fixation();

        /**
         * Used to set default parameters of fixation and add it into engines
         */
        void setup();

        /**
         * Used to create and attach a bone to the fixation
         */
        Bone *addBone(const btQuaternion &localOrientation, btScalar boneRadius, btScalar boneLenght, btScalar endFixRadius, const btVector3 &lowerLimits, const btVector3 &upperLimits);

        // TOOLS
        void fixeInTheAir(const btVector3 &position);
        void unfixInTheAir();
        inline bool isFixedInTheAir(){ return airFixation != 0; }

        // GETTERS AND SETTERS
        inline QList<Bone *> &getBones()               { return bones; }
        //inline OpenGLEngine *getOpenGLEngine()       { return openGLEngine; }
        inline BulletEngine *getBulletEngine()        { return bulletEngine; }
        inline btScalar getRadius()                    { return radius; }
        inline void setEntity(Entity *entity)          { this->entity = entity; }
        inline Entity *getEntity()                     { return entity; }
        btRigidBody *getRigidBody();
        FixationProperties *getInspectorWidget();
        void setSelected(bool isSelected);

        /**
         * The percent of penetration of bone into fixation (percent of fixation radius)
         */
        static const btScalar PERCENT_BONE_INSIDE_FIX;

    protected:

        btShapesFactory *shapesFactory;

        btTransform localFixation;
        btRigidBody *rigidBody;
        RigidBodyOrigin *origin;
        QList<Bone *> bones;

        btScalar radius;
        btSphere *sphere;

        //OpenGLEngine *openGLEngine;
        BulletEngine *bulletEngine;

        btTypedConstraint *airFixation;

        static FixationProperties *inspectorWidget;

        Entity *entity;

        bool delegatedSetup;

    };



//    class Fixation : public QObject
//    {
//        Q_OBJECT
//    public:
//        explicit Fixation(QObject *parent = 0);
//        ~Fixation();



//        Bone* addBone(float alpha,
//                     float beta,
//                     float length);

//        Bone* addBone(float alpha,
//                     float beta_min, float beta_max,
//                     float length);

//        Bone* addBone(float alpha,
//                     float beta,
//                     float r_min, float r_max,
//                     float length);

//        Bone* addBone(float alpha,
//                     float beta_min, float beta_max,
//                     float r_min, float r_max,
//                     float length);

//        // OgreBullet
//        /** create entity in Ogre and Bullet and attach all bones */
//        void initOgreBullet(OgreManager* ogreManager, BulletManager *bulletManager);
//        void setup(Ogre::Vector3 position);
//        OgreBulletDynamics::RigidBody *getRigidBody();


//        QList<Bone*> getArticulatedBones();
//        QString toString();

//        float getRadius();

//    signals:

//    public slots:

//    private:
//        QList<Bone*> articulatedBones;
//        OgreBulletDynamics::RigidBody *rigidBody;

//        OgreManager* ogreManager;
//        BulletManager *bulletManager;

//        float radius;
//    };
}
#endif // FIXATION_H
