#include "gravitysensor.h"

#include "body/fixation.h"
#include "bullet/btworld.h"
#include "btshapesfactory.h"
#include "tools.h"

namespace GeneCraftCore {

GravitySensor::GravitySensor(Fixation *fixation) : Sensor(fixation)
{
    typeName = "Gravity sensor";
    type = gravitySensor;

    axeX = new BrainIn(-1,1);
    axeY = new BrainIn(-1,1);
    axeZ = new BrainIn(-1,1);

    brainInputs.append(axeX);
    brainInputs.append(axeY);
    brainInputs.append(axeZ);
}

GravitySensor::GravitySensor(QVariant data, Fixation *fixation) : Sensor(data, fixation)
{
    axeX = new BrainIn(data.toMap()["axeX"]);
    axeY = new BrainIn(data.toMap()["axeY"]);
    axeZ = new BrainIn(data.toMap()["axeZ"]);

    brainInputs.append(axeX);
    brainInputs.append(axeY);
    brainInputs.append(axeZ);
}

QVariant GravitySensor::serialize()
{
    QVariantMap data = Sensor::serialize().toMap();
    data.insert("axeX", axeX->serialize());
    data.insert("axeY", axeY->serialize());
    data.insert("axeZ", axeZ->serialize());
    return data;
}

QVariant GravitySensor::generateEmpty()
{
    QVariantMap data = Sensor::generateEmpty("Gravity sensor", gravitySensor).toMap();

    BrainIn axeX(-1,1);
    BrainIn axeY(-1,1);
    BrainIn axeZ(-1,1);

    axeX.connectRandomly();
    axeY.connectRandomly();
    axeZ.connectRandomly();

    data.insert("axeX", axeX.serialize());
    data.insert("axeY", axeY.serialize());
    data.insert("axeZ", axeZ.serialize());

    return data;
}

void GravitySensor::step()
{
    btVector3 vect = fixation->getShapesFactory()->getWorld()->getBulletWorld()->getGravity();
    axeX->setValue(vect.getX());
    axeY->setValue(vect.getY());
    axeZ->setValue(vect.getZ());
}

}
