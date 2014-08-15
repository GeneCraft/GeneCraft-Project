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

#include "statisticsstorage.h"

namespace GeneCraftCore{

// To create the storage
StatisticsStorage::StatisticsStorage() {}

StatisticsStorage::~StatisticsStorage() {
    foreach(Statistic* stat, stats) {
        delete stat;
    }

    stats.clear();
}

// To register a statistics
Statistic * StatisticsStorage::registerStat(QString name, QString unit) {

    Statistic * s = new Statistic(name,unit);
    stats.insert(name, s);
    return s;
}

// To register a statistics
void StatisticsStorage::registerStat(QString name, Statistic *stat) {
    stats.insert(name, stat);
}

// To create or set a statistics value
void StatisticsStorage::setValue(QString name, btScalar value){
    stats.value(name)->setValue(value);
}

// To get all statistics values
QMap<QString, Statistic *> StatisticsStorage::getStatistics() {
    return QMap<QString, Statistic *>(stats);
}

// To get a statistics
btScalar StatisticsStorage::getValue(QString name){
    if(!stats.contains(name))
        return 0.0;

    return stats.value(name)->getValue();
}

// To know if a stats exist
bool StatisticsStorage::exists(QString name){
    return stats.contains(name);
}

void Statistic::resetAll(){

    if(resetable)
    {
        min = FLT_MAX;
        max = FLT_MIN;

        value = sum = 0.0;
        nbValues = 0;

        emit reseted();
    }
}

}
