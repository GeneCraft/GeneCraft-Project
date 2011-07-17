#ifndef BOXSMELLSENSOR_H
#define BOXSMELLSENSOR_H

#include "smellsensor.h"

namespace GeneLabCore {

class BoxSmellSensor : public SmellSensor
{
public:
    BoxSmellSensor(Fixation *fixation);

    // To create from serialization data
    BoxSmellSensor(QVariant data, Fixation * fixation);
};

}

#endif // BOXSMELLSENSOR_H
