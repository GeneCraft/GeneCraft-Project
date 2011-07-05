#ifndef STATISTIC_H
#define STATISTIC_H

#include <QString>

namespace GeneLabCore{

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Main class of all statistics. Statistics is used to know information about entities abilities or characteristics.
 * This notion is used to apply natural selection.
 *
 * @version 1.0 | July 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class Statistic
{
public:
    Statistic();

    // To define how to update statistic value
    virtual void update() = 0;

    // To get the name
    const QString &getName() { return name; }

    // To rename to a more precise name
    // (for ex.: root position rather than fixation position)
    void setName(const QString &name) { this->name = name; }

    // To get the unit
    const QString &getUnit() { return unit; }

    // To get the statistic value
    float getValue()
    {
        if(updateWhenValueIsRequested)
            update();

        return value;
    }

    // To reset
    virtual void reset() {}

    // To know if statistic need to be updated at each step
    bool wantToBeUpdatedEachStep() { return updateEachStep; }

protected:

    // The statistic value
    float value;

    // Name
    QString name;

    // Unit
    QString unit;

    // need to be updated at each step
    bool updateEachStep;

    // need to be updated when value is requested
    bool updateWhenValueIsRequested;
};

}

#endif // STATISTIC_H
