/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

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
