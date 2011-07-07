#ifndef STATISTICSSTORAGE_H
#define STATISTICSSTORAGE_H

#include <QMap>
#include <QString>
#include <float.h>

namespace GeneLabCore{

class Statistic
{
    public :

    Statistic(QString name, float initialValue, QString unit) :
        name(name), value(initialValue), min(FLT_MAX), max(FLT_MIN), unit(unit), nbValues(0), sum(0), resetable(true) {
    }

    // To get unit
    void setValue(float value)
    {
        this->value = value;

        // update min and max
        if(value < min)
            min = value;
        if(value > max)
            max = value;

        // update sum
        sum += value;

        // update number of steps
        nbValues++;
    }

    // To get unit
    float getValue() {
        return value;
    }

    // To get name
    const QString &getName() {
        return name;
    }

    // To get unit
    const QString &getUnit() {
        return unit;
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
    float getMean() {
        if(nbValues > 0)
            return sum / nbValues;
        else
            return 0.0;
    }

    // To get sum of values
    float getSum() {
        return sum;
    }

    // To reset
    void reset(){

        if(resetable)
        {
            min = FLT_MAX;
            max = FLT_MIN;

            value = sum = 0.0;
            nbValues = 0;
        }
    }

private:

    // The statistic values
    float value, min, max, sum;

    // To compute average
    int nbValues;

    bool resetable;

    QString name, unit;
};

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Statistics Storage stock all statistics identified by name.
 *
 * @version 1.0 | July 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class StatisticsStorage
{
public:

    // To create the storage
    StatisticsStorage();

    // To register a statistics
    Statistic * registerStat(QString name, float initialValue, QString unit);
    void registerStat(QString name, Statistic *stat);

    // To create or set a statistics value
    void setValue(QString name, float value);

    // To get all statistics values
    QMap<QString, Statistic *> getStatistics();

    // To get a statistics
    float getValue(QString name);

    // To know if a stats exist
    bool exists(QString name);

private:

    QMap<QString, Statistic *> stats;
};

}

#endif // STATISTICSSTORAGE_H
