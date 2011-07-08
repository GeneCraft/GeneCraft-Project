#include "statisticsstorage.h"

namespace GeneLabCore{

// To create the storage
StatisticsStorage::StatisticsStorage() {}

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
void StatisticsStorage::setValue(QString name, float value){
    stats.value(name)->setValue(value);
}

// To get all statistics values
QMap<QString, Statistic *> StatisticsStorage::getStatistics() {
    return QMap<QString, Statistic *>(stats);
}

// To get a statistics
float StatisticsStorage::getValue(QString name){
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
