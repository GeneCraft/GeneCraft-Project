

// Our namespace
namespace GeneLabCore {
    // An engine
    class Engine;

    // Entity related
    class Entity;
    class EntityFamily;

    // Neural network and brain engine
    class NeuralNetwork;
    class NeuralIn;
    class NeuralOut;
    class BrainEngine;

    // World related
    class World;

    // Generic simulation manager
    class SimulationManager;


}

namespace GeneLabWidget {

    // Neural network
    class NeuralNetworkVisualizer;

}

namespace GeneLabFactory {
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
}

namespace GeneLabOgreBullet {
    // Ogre management
    class OgreManager;
    class OgreScene;

    // Bullet management
    class BulletManager;
    class BulletScene;

    // Event management
    class EventManager;
    class InputListener;

    // Entity and world implementation
    //class OgreBulletScene;
    class OgreBulletEntity;
    class OgreBulletEntityFamily;

    class SnakeFamily;


    class TreeShape;
    class ArticulatedBone;
    class Fixation;
    class Articulation;

    // UI utils
    class OgreWidget;

    // UI Event
    class EventManager;
}

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
