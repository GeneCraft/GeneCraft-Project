#include "positionsensor.h"

#include "brainin.h"
#include "fixation.h"
#include <QDebug>

namespace GeneLabCore {
PositionSensor::PositionSensor(Fixation * rootFix, Fixation *fixation) : Sensor(fixation)
{
    this->rootFix = rootFix;

    typeName = "Egocentric position sensor";

    // WARNING : max size of an entity is 200 in this case ! FIXME
    // 200 c'est grand de toute fa�on :D
    // Je dirais plutot 20 !
    inputX = new BrainIn(-20.0,20.0);
    inputY = new BrainIn(-20.0,20.0);
    inputZ = new BrainIn(-20.0,20.0);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);
}

void PositionSensor::step()
{
    btTransform inverseRootTransform = rootFix->getRigidBody()->getWorldTransform().inverse();
    btVector3 distance = inverseRootTransform(fixation->getRigidBody()->getWorldTransform().getOrigin());

    // Small fixe, now use the rootTransform orientation !!!
    /* btVector3 distance = fixation->getRigidBody()->getWorldTransform().getOrigin()
            - rootFix->getRigidBody()->getWorldTransform().getOrigin();
    */

    //qDebug() << "PositionSensor::step() x = " << distance.x() << " y = " << distance.y() << " z = " << distance.z();

    inputX->setValue(distance.x());
    inputY->setValue(distance.y());
    inputZ->setValue(distance.z());
}
}
