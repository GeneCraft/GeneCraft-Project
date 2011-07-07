#ifndef STATISTIC_H
#define STATISTIC_H

#include <QString>
#include <float.h>
#include <QDebug>

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

    // To step the statisitc
    virtual void step()
    {
        if(updateEachStep){

            // update value
            update();

            // update min and max
            if(value < min)
                min = value;
            if(value > max)
                max = value;

            // update sum
            sum += value;

            // update number of steps
            nbSteps++;
        }
    }

    virtual void update() = 0;

    // To get name
    const QString &getName() { return name; }

    // To rename to a more precise name
    // (for ex.: root position rather than fixation position)
    void setName(const QString &name) { this->name = name; }

    // To get unit
    const QString &getUnit() { return unit; }

    // To get current value
    float getValue()
    {
        if(updateWhenValueIsRequested) {

            update();

            // update min and max
            if(value < min)
                min = value;
            if(value > max)
                max = value;
        }

        return value;
    }

    // To get minimal value
    float getMinValue() {
        return min;
    }

    // To get maximal value
    float getMaxValue() {
        return max;
    }

    // To get average value
    float getAverage() {

        if(nbSteps > 0)
            return sum / nbSteps;
        else
            return 0.0;
    }

    // To get sum of values
    float getSum() {
        return sum;
    }

    // To reset
    virtual void reset()
    {
        qDebug() << FLT_MIN << FLT_MAX;

        min = FLT_MAX;
        max = FLT_MIN;
        value = sum = 0.0;
        nbSteps = 0;
    }

    // To know if statistic need to be updated at each step
    bool wantToBeUpdatedEachStep() { return updateEachStep; }

protected:

    // The statistic values
    float value, min, max, sum;

    // To compute average
    int nbSteps;

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
