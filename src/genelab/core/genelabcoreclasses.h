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
    class BrainEngine;

    // Generic simulation manager
    class SimulationManager;


    // --------------
    // -- entities --
    // --------------
    class Entity;

    // Families
    class EntityFamily;
    class SnakeFamily;

    // Body
    class TreeShape;
    class Bone;
    class Fixation;

    // Brain
    // Neural network
    class NeuralNetwork;
    class NeuralIn;
    class NeuralOut;


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
    class NeuralNetworkVisualizer;



    // -----------------------
    // -- DELETE OR NOT ??? --
    // -----------------------

    // World related
    class World;

    // Entity and world implementation
    //class OgreBulletScene;
    class OgreBulletEntity;
    class OgreBulletEntityFamily;

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
