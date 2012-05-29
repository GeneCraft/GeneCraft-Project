#ifndef REALSPIDERENTITY_H
#define REALSPIDERENTITY_H

#include "entity.h"
#include <QList>
#include "entities/body/leg.h"

namespace GeneCraftCore {

class realSpiderEntity : public Entity
{
public:
    realSpiderEntity(QString name, QString family, QString type, int generation, QObject *parent = 0);
    void setup();
    void addLeftLeg(Leg* leg);
    void addRightLeg(Leg* leg);
    void removeLeftLeg(int leg);
    void removeRightLeg(int leg);
    void removeAllRightLegs();
    void removeAllLeftLegs();
    void removeAllLegs();
protected:
    QList<Leg*> leftLegs;
    QList<Leg*> rightLegs;
};
}

#endif // REALSPIDERENTITY_H
