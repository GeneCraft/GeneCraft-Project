#include "ogrebulletentity.h"
#include "struct/articulation.h"
#include "sandboxtools.h"
#include "struct/treeshape.h"
#include "struct/fixation.h"
#include "struct/articulatedbone.h"
#include "struct/types.h"
#include <QList>
#include <QStack>
#include "graphic/ogremanager.h"
#include "physics/bulletmanager.h"
#include "Dynamics/Constraints/OgreBulletDynamics6DofConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "Dynamics/OgreBulletDynamicsRigidBody.h"
#include "Dynamics/Constraints/OgreBulletDynamicsPoint2pointConstraint.h"

namespace GeneLabOgreBullet {
    OgreBulletEntity::OgreBulletEntity(QString name, QString f, int gen, QObject *parent) :
        GeneLabCore::Entity(name, f, gen)
    {}

    void OgreBulletEntity::initOgreBullet(OgreManager* ogreManager, BulletManager* bulletManager)
    {
        this->ogreManager = ogreManager;
        this->bulletManager = bulletManager;

        // TODO add ogreManager and bulletManager to all fixation...
    }

    void OgreBulletEntity::setup()
    {
        // Setup the shape
        shape->initOgreBullet(ogreManager,bulletManager);
        shape->setup();
    }

    void OgreBulletEntity::setShape(TreeShape *shape) {
        this->shape = shape;
    }

    TreeShape* OgreBulletEntity::getShape() {
        return this->shape;
    }
}
