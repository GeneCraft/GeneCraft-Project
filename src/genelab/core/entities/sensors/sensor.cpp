#include "sensor.h"

namespace GeneLabCore {
Sensor::Sensor(Fixation * fixation, QObject *parent) :
    QObject(parent)
{
    this->fixation = fixation;
}
}
