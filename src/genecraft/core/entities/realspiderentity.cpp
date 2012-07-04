#include "realspiderentity.h"
namespace GeneCraftCore {

RealSpiderEntity::RealSpiderEntity(QString name, QString family, QString type, int generation, QObject *parent):
    Entity(name, family, type, generation, parent)
{

}

void RealSpiderEntity::setup()
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

void RealSpiderEntity::addLeftLeg(Leg *leg)
{
    leftLegs.append(leg);
}

void RealSpiderEntity::addRightLeg(Leg *leg)
{
    rightLegs.append(leg);
}

void RealSpiderEntity::removeLeftLeg(int leg)
{
    leftLegs.removeAt(leg);
}

void RealSpiderEntity::removeRightLeg(int leg)
{
    rightLegs.removeAt(leg);
}

void RealSpiderEntity::removeAllLeftLegs()
{
    leftLegs.clear();
}

void RealSpiderEntity::removeAllRightLegs()
{
    rightLegs.clear();
}

void RealSpiderEntity::removeAllLegs()
{
    removeAllRightLegs();
    removeAllLeftLegs();
}

QVariant RealSpiderEntity::serialize()
{
    QVariantMap entityVariant = Entity::serialize().toMap();

    entityVariant.insert("params", parameters.toMap());

    return entityVariant;
}

void RealSpiderEntity::setParams(QVariant params)
{
    parameters = params;
}

QVariant RealSpiderEntity::getParams()
{
    return parameters;
}

}
