#ifndef GENLAB_CLASSES_H
#define GENLAB_CLASSES_H

// Our namespace
namespace GeneLabCore {

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
    class btBone;

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
    // Testing purpose
    class SinusIn;

    // Sensors
    class Sensor;
    class PositionSensor;
    class GyroscopicSensor;
    class AccelerometerSensor;
    class ContactSensor;

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

    // ----------------
    // -- Ressources --
    // ----------------
    class Ressource;    // (file, db, etc.)
    class JsonLoader;   // Ressource management


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

    // -----------------------
    // -- DELETE OR NOT ??? --
    // -----------------------

    // Tools (random, ...)
    class Tools;
}

// Entities
class BonePropertiesController;
class FixationPropertiesController;

// Experiment
class FloatMutationController;
class IntegerMutationController;
class SimpleProbabilityController;

// Typical used ogre namespace classes
namespace Ogre {
    class Root;
    class SceneManager;
    class RenderWindow;
    class Camera;
    class Vector3;
    class Viewport;
}

// OgreBullets most used classes
namespace OgreBulletDynamics {
    class DynamicsWorld;
    class RigidBody;
    class SixDofConstraint;
}

namespace OgreBulletCollisions {
    class DebugDrawer;
    class CollisionShape;
}

#endif
