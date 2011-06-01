#ifndef SPIDER_H
#define SPIDER_H

#include "genelabcoreclasses.h"
#include "LinearMath/btTransform.h"
#include "entityfamily.h"

namespace GeneLabCore {

class Spider : public EntityFamily
{
    Q_OBJECT

public:

    Spider();
    virtual Entity* createEntity(btShapesFactory *shapesFactory,
                                 const btVector3 &position);

    virtual QVariant serialize();
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
    void addLeg(Fixation *fixBody, btScalar yAxis, btScalar zAxis, const btVector3 &lowerLimits, const btVector3 &upperLimits);
};

}

#endif // SPIDER_H
