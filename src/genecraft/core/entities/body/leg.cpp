#include "leg.h"

#include "body/fixation.h"
#include "body/bone.h"
#include <QDebug>
#include "entities/effectors/rotationalmotorseffector.h"
#include "entities/effectors/brainoutmotor.h"
#include "entity.h"

#include "entities/effectors/legeffector.h"

#define AXE_X 0
#define AXE_Y 1
#define AXE_Z 2

namespace GeneCraftCore {

Leg::Leg(int rightSide, int nbBone, Fixation *fixBody, btScalar *yAxis, btScalar *zAxis, btScalar kneeRadius, btVector3 *lowerLimits, btVector3 *upperLimits, btScalar *legSegmentRadius, btScalar *legSegmentLength)
{
    this->rightSide = rightSide;
    this->nbBoneInLeg = nbBone;
    this->anglesY = yAxis;
    this->anglesZ = zAxis;
    this->kneeRadius = kneeRadius;
    this->lowerLimits = lowerLimits;
    this->upperLimits = upperLimits;
    this->legSegmentLength = legSegmentLength;
    this->legSegmentRadius = legSegmentRadius;

    Bone *rootBone = fixBody->addBone(anglesY[0], anglesZ[0],
                                      btScalar(legSegmentRadius[0]),
                                      btScalar(legSegmentLength[0]),
                                      btScalar(kneeRadius),
                                      lowerLimits[0],
                                      upperLimits[0]);

    firstBone = rootBone;
    rootBone->getEndFixation()->addEffector(new LegEffector(this));

    for(int i=1;i<nbBoneInLeg;++i)
    {
        bones.append(rootBone);
        rootBone = rootBone->getEndFixation()->addBone(rightSide*anglesY[i], anglesZ[i],
                                                       btScalar(legSegmentRadius[i]),
                                                       btScalar(legSegmentLength[i]),
                                                       btScalar(kneeRadius),
                                                       lowerLimits[i],
                                                       upperLimits[i]);

        //rootBone->getEndFixation()->addSensor(new AccelerometerSensor(rootBone->getEndFixation()));

        //rootBone->getEndFixation()->addSensor(new PositionSensor(fixBody, rootBone->getEndFixation()));

        //rootBone->getParentConstraint()->setAngularLowerLimit(btVector3(0,0,0));
        //rootBone->getParentConstraint()->setAngularUpperLimit(btVector3(0,0,0));
    }
    bones.append(rootBone);
    // dernier os -> getEndFixation();
    contact =  new ContactSensor(rootBone->getEndFixation());
    rootBone->getEndFixation()->addSensor(contact);

    // dernier os -> getEndFixation();
    gripper = new GripperEffector(rootBone->getEndFixation());
    // on veut le faire nous meme, donc on l'ajoute pas rootBone->getEndFixation()->addEffector(gripper);
}

Leg* Leg::createLeftLeg(int nbBone, Fixation *fixBody, btScalar *yAxis, btScalar *zAxis, btScalar kneeRadius, btVector3 *lowerLimits, btVector3 *upperLimits, btScalar *legSegmentRadius, btScalar *legSegmentLength)
{
    return new Leg(-1, nbBone, fixBody, yAxis, zAxis, kneeRadius, lowerLimits, upperLimits, legSegmentRadius, legSegmentLength);
}

Leg* Leg::createRightLeg(int nbBone, Fixation *fixBody, btScalar *yAxis, btScalar *zAxis, btScalar kneeRadius, btVector3 *lowerLimits, btVector3 *upperLimits, btScalar *legSegmentRadius, btScalar *legSegmentLength)
{
    return new Leg(1, nbBone, fixBody, yAxis, zAxis, kneeRadius, lowerLimits, upperLimits, legSegmentRadius, legSegmentLength);
}

void Leg::setup(Entity * e)
{
    foreach(Bone* b, bones)
    {
        for(int i = 0; i < 3 ; i++)
        {
            if(b->getRotationalMotorsEffector()->getBrainOutputs(i))
            {
                e->removeBrainOut(b->getRotationalMotorsEffector()->
                                  getBrainOutputs(i)->boMaxMotorForce);
                e->removeBrainOut(b->getRotationalMotorsEffector()->
                                  getBrainOutputs(i)->boTargetVelocity);
            }
        }
    }
}

void Leg::legUp()
{
    // Gripper se trouvant en bout de patte doit se d�tacher du sol
    gripper->unfix();

    //Avancer premier os
    ((Bone*)bones.at(0))->getRotationalMotorsEffector()->
            getBrainOutputs(AXE_X)->boMaxMotorForce->setValue(rightSide*1);
    ((Bone*)bones.at(0))->getRotationalMotorsEffector()->
            getBrainOutputs(AXE_X)->boTargetVelocity->setValue(rightSide*(-200));

    //Monter deuxi�me os
    ((Bone*)bones.at(1))->getRotationalMotorsEffector()->
            getBrainOutputs(AXE_Z)->boMaxMotorForce->setValue(-1);
    ((Bone*)bones.at(1))->getRotationalMotorsEffector()->
            getBrainOutputs(AXE_Z)->boTargetVelocity->setValue(200);

    //Monter troisi�me os
    ((Bone*)bones.at(2))->getRotationalMotorsEffector()->
            getBrainOutputs(AXE_Z)->boMaxMotorForce->setValue(-1);
    ((Bone*)bones.at(2))->getRotationalMotorsEffector()->
            getBrainOutputs(AXE_Z)->boTargetVelocity->setValue(200);

    //Monter quatrieme os
    ((Bone*)bones.at(3))->getRotationalMotorsEffector()->
            getBrainOutputs(AXE_Z)->boMaxMotorForce->setValue(-1);
    ((Bone*)bones.at(3))->getRotationalMotorsEffector()->
            getBrainOutputs(AXE_Z)->boTargetVelocity->setValue(200);

}

void Leg::legDown()
{
    // Descendre
    //qDebug() << "DOWN";
    if(contact->hasCollided())
    {
        gripper->fix();

        //Reculer premier os
        ((Bone*)bones.at(0))->getRotationalMotorsEffector()->
                getBrainOutputs(AXE_X)->boMaxMotorForce->setValue(rightSide*(-1));
        ((Bone*)bones.at(0))->getRotationalMotorsEffector()->
                getBrainOutputs(AXE_X)->boTargetVelocity->setValue(rightSide*200);
    }

    //Monter deuxi�me os
    ((Bone*)bones.at(1))->getRotationalMotorsEffector()->getBrainOutputs(AXE_Z)->boMaxMotorForce->setValue(1);
    ((Bone*)bones.at(1))->getRotationalMotorsEffector()->getBrainOutputs(AXE_Z)->boTargetVelocity->setValue(-200);

    //Monter troisi�me os
    ((Bone*)bones.at(2))->getRotationalMotorsEffector()->getBrainOutputs(AXE_Z)->boMaxMotorForce->setValue(1);
    ((Bone*)bones.at(2))->getRotationalMotorsEffector()->getBrainOutputs(AXE_Z)->boTargetVelocity->setValue(-200);

    //Monter quatrieme os
    ((Bone*)bones.at(3))->getRotationalMotorsEffector()->getBrainOutputs(AXE_Z)->boMaxMotorForce->setValue(1);
    ((Bone*)bones.at(3))->getRotationalMotorsEffector()->getBrainOutputs(AXE_Z)->boTargetVelocity->setValue(-200);
}

}
