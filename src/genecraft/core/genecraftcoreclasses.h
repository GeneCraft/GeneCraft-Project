#ifndef GENECRAFTCORECLASSES_H
#define GENECRAFTCORECLASSES_H

#include "LinearMath/btTransform.h"

// Our namespace
namespace GeneCraftCore {

    // -------------
    // -- engines --
    // -------------
    class Engine;

    // Bullet management
    class BulletEngine;
    class RigidBodyOrigin; // user pointer
    class btBox;
    class btSphere;
    class btCylinder;
    class btPhysBone;

    // Ogre management
    class OgreEngine;

    // Bullet & Ogre linker
    class BulletOgreEngine;
    class btoBox;
    class btoSphere;
    class btoCylinder;

    // Event management
    class EventsManager;
    class InputListener;
    class InspectorsInputManager;

    // OpenGL
    class OpenGLEngine;

    // Brain
    class EntitiesEngine;

    // Generic simulation manager
    class SimulationManager;


    // --------------
    // -- entities --
    // --------------
    class Entity;

    // Families
    class EntityFamily;
    class SnakeFamily;
    class GenericFamily;

    // Body
    class TreeShape;
    class Bone;
    class Fixation;

    // Brain
    // Interconnexion classes
    class BrainIn;
    class BrainOut;
    // Interconnexion layer
    class BrainPlugGrid;
    // Generic brain classe
    class Brain;
    // Functionnal like brain style
    class BrainFunctional;
    // Function bloc of the functionalbrain
    class BrainNode;
    class BrainNodeIn;
    // Testing purpose
    class SinusIn;

    class BrainOutMotor;

    // Sensors
    class Sensor;
    class PositionSensor;
    class GyroscopicSensor;
    class AccelerometerSensor;
    class ContactSensor;
    class SmellSensor;

    // Effector
    class FlyingEffector;

    // Modifier
    class Effector;
    class RotationalMotorsEffector;

    // Statistics
    class StatisticsProvider;
    class StatisticsStorage;

    // ---------------
    // -- Factories --
    // ---------------
    class btFactory;
    class btoFactory;

    // Shapes
    class btShapesFactory;
    class btglShapesFactory;
    class btoShapesFactory;

    class CreatureFactory;
    class btoWorldFactory;
    class btWorldFactory;

    // ----------------
    // -- Experiment --
    // ----------------
    class Experiment;
    class ExperimentManager;
    class Result;
    class MutationsManager;
    class Mutation;
    class FloatMutation;
    class IntegerMutation;
    class SimpleProbabilityMutation;
    class StructuralMutation;
    class StructuralList;
    class MutationElement;

    // ----------------
    // -- Ressources --
    // ----------------
    class Ressource;    // (file, db, etc.)
    class JsonLoader;   // Ressource management
    class RessourcesManager;

    // --------
    // -- UI --
    // --------
    // UI utils
    class OgreWidget;
    class OgreBulletWindows;

    // Neural network
    class PlugGridVisualizer;
    class PlugGridDesignVisualizer;

    // -----------------------
    // -- World related     --
    // -----------------------

    class btWorld;
    class btScene;
    class btBiome;

    class btoWorld;
    class btoScene;
    class btoBiome;

    class Spawn;


    class Terrain;
    class TerrainData;

    /*
      Shape
      */
    class Box;
    class Cylinder;
    class Sphere;
    class PhysBone;

    class btBox;
    class btCylinder;
    class btPhysBone;
    class btSphere;

    class oBox;
    class oCylinder;
    class oPhysBone;
    class oSphere;
/*
    class cmBox;
    class cmCylinder;
    class cmPhysBone;
    class cmSphere;
*/
    class Link;
    class Linked;
    template <class T> class Node;
    class LinkEngine;

    // -----------------------
    // -- DELETE OR NOT ??? --
    // -----------------------

    // Tools (random, ...)
    class Tools;

}



// Bullet
class btVector3;
class btDiscreteDynamicsWorld;
class btOverlappingPairCache;
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDynamicsWorld;
class btGeneric6DofConstraint;
class btRigidBody;

// Entities
class BonePropertiesController;
class FixationPropertiesController;

// Experiment
class FloatMutationController;
class IntegerMutationController;
class SimpleProbabilityController;
class StructuralMutationController;

// Typical used ogre namespace classes
namespace Ogre {
    class Root;
    class SceneManager;
    class RenderWindow;
    class Camera;
    class Vector3;
    class Viewport;
}


#endif
