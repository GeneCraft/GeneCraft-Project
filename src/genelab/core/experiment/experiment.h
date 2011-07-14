#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "result.h"
#include <QList>
#include <QDebug>
#include <QVariantMap>
#include <QDir>

namespace GeneLabCore {
    class Experiment
    {
    public:
        Experiment(QVariant data);

        /**
          * Experiment name, or id
          */
        QString getId() {
            return this->id;
        }

        /**
          * The experience description given by the creator
          */
        QString getDescription() {
            return this->description;
        }


        /**
          * The actual experiment informations, must be parsed and stored in a struct
          */
        QVariantMap getExpData() {
            return this->expData;
        }

        QVariantMap getSeedInfo() {
            return this->seedInfo;
        }

        int getExpTime() {
            return this->expTime;
        }

    protected:
        QString id;
        QString description;
        QVariantMap expData;

        Ressource* expFile;

        int expTime;

        QVariantMap seedInfo;

    };
}

#endif // EXPERIMENT_H
