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

// Our namespace
namespace GeneLabCore {
    // Graphical related
    class GraphicsEngine;
    class GraphicsScene;

    // Physical related
    class PhysicsEngine;
    class PhysicsScene;

    // Entity related
    class EntityGraphics;
    class EntityPhysics;
    class World;

    // World related
    class WorldGraphics;
    class WorldPhysics;
    class Entity;
}

namespace GeneLabOgreBullet {
    // Ogre management
    class OgreManager;
    class OgreScene;

    // Bullet management
    class BulletManager;
    class BulletScene;

    // Entity and world implementation
    class OgreBulletWorld;
    class OgreBulletEntity;

    // UI utils
    class OgreWidget;
}
