/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef STATISTICSSTORAGE_H
#define STATISTICSSTORAGE_H

#include <QObject>
#include <QMap>
#include <QString>
#include"LinearMath/btScalar.h"

namespace GeneCraftCore{

class Statistic : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY(type name
               READ getFunction
               [WRITE setFunction]
               [RESET resetFunction]
               [DESIGNABLE bool]
               [SCRIPTABLE bool]
               [STORED bool])*/
    Q_PROPERTY(float value READ getValue WRITE setValue)
    Q_PROPERTY(float min READ getMinValue)
    Q_PROPERTY(float max READ getMaxValue)
    Q_PROPERTY(float mean READ getMean)
    Q_PROPERTY(float sum READ getSum)


    public :

    Statistic(QString name, QString unit) :
        name(name), unit(unit), value(0), min(FLT_MAX), max(FLT_MIN), sum(0), nbValues(0), resetable(true) {
    }

    // To get unit
    void setValue(btScalar value)
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
    btScalar getValue() {
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
    btScalar getMinValue() {
        return min;
    }

    // To get maximal value
    btScalar getMaxValue() {
        return max;
    }

    // To get average value
    btScalar getMean() {
        if(nbValues > 0)
            return sum / nbValues;
        else
            return 0.0;
    }

    // To get sum of values
    btScalar getSum() {
        return sum;
    }

    // To reset
    void resetAll();
    void setResetable(bool resetable) {
        this->resetable = resetable;
    }

signals:

    void reseted();

private:

    QString name, unit;

    // The statistic values
    btScalar value, min, max, sum;

    // To compute average
    int nbValues;

    bool resetable;

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
    ~StatisticsStorage();

    // To register a statistics
    Statistic * registerStat(QString name, QString unit);
    void registerStat(QString name, Statistic *stat);

    // To create or set a statistics value
    void setValue(QString name, btScalar value);

    // To get all statistics values
    QMap<QString, Statistic *> getStatistics();

    // To get a statistics
    btScalar getValue(QString name);

    // To know if a stats exist
    bool exists(QString name);

private:

    QMap<QString, Statistic *> stats;
};

}

#endif // STATISTICSSTORAGE_H
