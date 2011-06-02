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
    class EventManager;
    class InputListener;

    // OpenGL
    class OpenGLEngine;

    // Brain
    class BrainEngine; // TODO DELETE !
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
    class Modifier;
    class RotationalMotorsModifier;

    // ---------------
    // -- Factories --
    // ---------------
    class MainFactory;
    class EntityFactory;
    class EngineFactory;
    class WorldFactory;

    // Neural
    class NeuralNetworkFactory;

    // Shapes
    class btShapesFactory;
    class btglShapesFactory;
    class btoShapesFactory;

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



    // -----------------------
    // -- DELETE OR NOT ??? --
    // -----------------------

    // World related
    class World;

    // Tools (random, ...)
    class Tools;
}

// Entities
class BonePropertiesController;
class FixationProperties;

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
