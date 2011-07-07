#include "statisticsstorage.h"

namespace GeneLabCore{

// To create the storage
StatisticsStorage::StatisticsStorage() {}

// To register a statistics
Statistic * StatisticsStorage::registerStat(QString name, float initialValue, QString unit) {

    Statistic * s = new Statistic(name, initialValue,unit);
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
    return stats.value(name)->getValue();
}

// To know if a stats exist
bool StatisticsStorage::exists(QString name){
    return stats.contains(name);
}

}
