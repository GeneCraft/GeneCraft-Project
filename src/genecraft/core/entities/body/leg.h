#ifndef LEG_H
#define LEG_H

#include <QObject>
#include <QVariant>

#include "genecraftcoreclasses.h"
#include "entities/sensors/contactsensor.h"
#include "entities/effectors/grippereffector.h"
#include "entities/sensors/distancesensor.h"

#include "LinearMath/btQuaternion.h"

namespace GeneCraftCore {

class Leg : public QObject
{

public:
    static Leg* createRightLeg(int nbBone, Fixation *fixBody, btScalar* yAxis, btScalar* zAxis, btScalar kneeRadius, btVector3* lowerLimits, btVector3* upperLimits, btScalar* legSegmentRadius, btScalar* legSegmentLength);
    static Leg* createLeftLeg(int nbBone, Fixation *fixBody, btScalar* yAxis, btScalar* zAxis, btScalar kneeRadius, btVector3* lowerLimits, btVector3* upperLimits, btScalar* legSegmentRadius, btScalar* legSegmentLength);
    void setup(Entity *e);
    void legUp();
    void legDown();

signals:
    
public slots:

private:

    QList<Bone*> bones;

    int rightSide;

    int nbBoneInLeg;

    Bone* firstBone;

    btScalar* legSegmentRadius;
    btScalar* legSegmentLength;
    btScalar kneeRadius;

    btScalar* anglesY;
    btScalar* anglesZ;

    btVector3* lowerLimits;
    btVector3* upperLimits;

    GripperEffector* gripper;
    ContactSensor* contact;

    Leg(int rightSide, int nbBone, Fixation *fixBody, btScalar* yAxis, btScalar* zAxis, btScalar kneeRadius, btVector3* lowerLimits, btVector3* upperLimits, btScalar* legSegmentRadius, btScalar* legSegmentLength);
    
};
}

#endif // LEG_H
