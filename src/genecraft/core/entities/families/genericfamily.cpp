#include "genericfamily.h"

#include "entity.h"
#include "body/treeshape.h"
#include "body/fixation.h"
#include "body/bone.h"
#include "brain/brainfunctional.h"
#include "tools.h"

#include "sensors/accelerometersensor.h"
#include "sensors/boxsmellsensor.h"
#include "sensors/contactsensor.h"
#include "sensors/distancesensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/positionsensor.h"
#include "sensors/sensor.h"
#include "sensors/smellsensor.h"

#include "effectors/effector.h"
#include "effectors/flyingeffector.h"
#include "effectors/grippereffector.h"
#include "effectors/rotationalmotorseffector.h"

namespace GeneCraftCore {
GenericFamily::GenericFamily()
{
}

Entity *GenericFamily::createVirginEntity(btShapesFactory *shapesFactory,
                                                btScalar rootFixRadius,
                                                const btVector3 &initialPosition)
{
    Entity * entity = new Entity("no name", "no family","generic", 1);
    entity->setBrain(new BrainFunctional());

    TreeShape *shape = new TreeShape(shapesFactory);

    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(initialPosition);

    shape->setRoot(new Fixation(shapesFactory,rootFixRadius,initTransform));
    entity->setShape(shape);

    return entity;
}
}
