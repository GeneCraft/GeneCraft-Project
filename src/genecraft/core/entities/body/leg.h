#ifndef LEG_H
#define LEG_H

#include <QObject>
#include <QVariant>

#include "genecraftcoreclasses.h"

namespace GeneCraftCore {

class Leg : public QObject
{

public:
    Leg(int rightSide, int legId, Fixation *fixBody, btScalar yAxis);
    
signals:
    
public slots:

private:

    int nbBoneInLeg;

    btScalar legRadius;
    btScalar legLenght;
    btScalar kneeRadius;

    btScalar** anglesY;
    btScalar* anglesZ;

    btVector3* lowerLimits;
    btVector3* upperLimits;
    
};
}

#endif // LEG_H
