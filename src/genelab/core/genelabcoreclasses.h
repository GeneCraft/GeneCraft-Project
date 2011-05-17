// Our namespace
namespace GeneLabCore {
    // An engine
    class Engine;

    // Entity related
    class Entity;
    class EntityFamily;
    class Bone;
    class Fixation;

    // Neural network and brain engine
    class NeuralNetwork;
    class NeuralIn;
    class NeuralOut;
    class BrainEngine;

    // World related
    class World;

    // Generic simulation manager
    class SimulationManager;

    // Creation
    class MainFactory;
    class EntityFactory;
    class EngineFactory;
    class WorldFactory;
    class NeuralNetworkFactory;

    // Ressource (file, db, etc.)
    class Ressource;

    // Ressource management
    class JsonLoader;

    // Neural network
    class NeuralNetworkVisualizer;

    // Ogre management
    class OgreManager;

    // Bullet management
    class BulletManager;

    // Event management
    class EventManager;
    class InputListener;

    // Entity and world implementation
    //class OgreBulletScene;
    class OgreBulletEntity;
    class OgreBulletEntityFamily;

    class SnakeFamily;


    class TreeShape;
    class Bone;
    class Fixation;
    class Articulation;

    // UI utils
    class OgreWidget;

    // UI Event
    class EventManager;

    class OgreBulletWindows;

    // Bullet user
    class RigidBodyOrigin;

    class Tools;
}

// UI Entities
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
