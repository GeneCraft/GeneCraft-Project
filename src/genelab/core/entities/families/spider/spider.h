#ifndef SPIDER_H
#define SPIDER_H

#include "genelabcoreclasses.h"
#include "LinearMath/btTransform.h"
#include "entity.h"

namespace GeneLabCore {

class Spider : public Entity
{
    Q_OBJECT

public:

    Spider(btShapesFactory *shapesFactory, const btVector3 &position);

protected:

    btVector3 initialPosition;
    btShapesFactory *shapesFactory;

    int nbLegs;
    int nbBoneInLeg;
    btScalar legRadius;
    btScalar legLenght;
    btScalar kneeRadius;

private:

    // use to create the spider
    void addLeg(Fixation *fixBody, const btTransform &localFix, const btVector3 &lowerLimits, const btVector3 &upperLimits);
};

}

#endif // SPIDER_H
