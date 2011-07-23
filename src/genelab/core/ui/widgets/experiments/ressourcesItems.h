#ifndef RESSOURCESITEMS_H
#define RESSOURCESITEMS_H

#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QVariantMap>
#include <ressources/ressourcesmanager.h>
#include "result.h"

namespace GeneLabCore{

// TREE

class ExperimentTreeWidgetItem : public QTreeWidgetItem
{
public:

    ExperimentTreeWidgetItem(DataWrapper dataw)
    {
        this->dataw = dataw;

        setText(0,dataw.data["_id"].toString());
        setText(1,dataw.data["author"].toString());
        setText(2,dataw.data["dateOfCreation"].toString());
    }

    DataWrapper dataw;
};


class ResultTreeWidgetItem : public QTreeWidgetItem
{
public:

    ResultTreeWidgetItem(Result *r)
    {
        this->r = r;

        setText(0, QString::number(r->getFitness(), 10, 2));
        setText(1, r->getWorker());
        setText(2, r->getDate());
    }

    Result * r;
};

class EntityTreeWidgetItem : public QTreeWidgetItem
{
public:

    EntityTreeWidgetItem(DataWrapper dataw)
    {
        this->dataw = dataw;

        QVariantMap origins = dataw.data["origins"].toMap();

        if(dataw.data.contains("_id")) {
            origins["name"] = dataw.data["_id"];
        }

        setText(0,origins["name"].toString());
        setText(1,origins["family"].toString());
        setText(2,origins["generation"].toString());
    }

    EntityTreeWidgetItem(QVariantMap genomeMap)
    {
        dataw.data = genomeMap;
        dataw.r = NULL;

        QVariantMap origins = dataw.data["origins"].toMap();

        if(dataw.data.contains("_id")) {
            origins["name"] = dataw.data["_id"];
        }

        setText(0,origins["name"].toString());
        setText(1,origins["family"].toString());
        setText(2,origins["generation"].toString());
    }

    DataWrapper dataw;
};

}

#endif // RESSOURCESITEMS_H
