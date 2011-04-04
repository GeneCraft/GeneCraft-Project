

// Our namespace
namespace GeneLabCore {
    // An engine
    class Engine;

    // Entity related
    class Entity;
    class EntityFamily;

    // World related
    class World;
}

namespace GeneLabOgreBullet {
    // Ogre management
    class OgreManager;
    class OgreScene;

    // Bullet management
    class BulletManager;
    class BulletScene;

    // Entity and world implementation
    //class OgreBulletScene;
    class OgreBulletWorld;
    class OgreBulletEntity;
    class OgreBulletEntityFamily;

    class TreeShape;
    class Bone;
    class Fixation;

    // UI utils
    class OgreWidget;
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
