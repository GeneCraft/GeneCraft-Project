

// Our namespace
namespace GeneLabCore {
    // An engine
    class Engine;

    // Entity related
    class Entity;
    class EntityFamily;

    // World related
    class World;

    // Generic simulation manager
    class SimulationManager;

}

namespace GeneLabFactory {
    // Creation
    class MainFactory;
    class EntityFactory;
    class EngineFactory;
    class WorldFactory;

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
    class Bone;
    class Fixation;

    // UI utils
    class OgreWidget;

    // UI Event
    class EventManager;

    // Simulation
    class OgreBulletSimulationManager;

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
}
namespace OgreBulletCollisions {
    class DebugDrawer;
    class CollisionShape;
}
