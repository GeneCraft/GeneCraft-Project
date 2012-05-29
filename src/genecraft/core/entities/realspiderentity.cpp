#include "realspiderentity.h"
namespace GeneCraftCore {

realSpiderEntity::realSpiderEntity(QString name, QString family, QString type, int generation, QObject *parent):
    Entity(name, family, type, generation, parent)
{

}

void realSpiderEntity::setup()
{
    Entity::setup();
    for(int i=0;i<leftLegs.size();i++)
    {
        ((Leg*)leftLegs.at(i))->setup(this);
    }
    for(int i=0;i<rightLegs.size();i++)
    {
        ((Leg*)rightLegs.at(i))->setup(this);
    }
}

void realSpiderEntity::addLeftLeg(Leg *leg)
{
    leftLegs.append(leg);
}

void realSpiderEntity::addRightLeg(Leg *leg)
{
    rightLegs.append(leg);
}

void realSpiderEntity::removeLeftLeg(int leg)
{
    leftLegs.removeAt(leg);
}

void realSpiderEntity::removeRightLeg(int leg)
{
    rightLegs.removeAt(leg);
}

void realSpiderEntity::removeAllLeftLegs()
{
    leftLegs.clear();
}

void realSpiderEntity::removeAllRightLegs()
{
    rightLegs.clear();
}

void realSpiderEntity::removeAllLegs()
{
    removeAllRightLegs();
    removeAllLeftLegs();
}

}
