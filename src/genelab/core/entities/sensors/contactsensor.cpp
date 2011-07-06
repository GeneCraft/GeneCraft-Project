#include "contactsensor.h"

namespace GeneLabCore {

// To create
ContactSensor::ContactSensor(Fixation * fixation) : Sensor(fixation){}

// To create from serialization data
ContactSensor::ContactSensor(QVariant data, Fixation * fixation) : Sensor(fixation) {}

// To serialize
QVariant ContactSensor::serialize(){}

// To update brain inputs values
void ContactSensor::step() {}

}
