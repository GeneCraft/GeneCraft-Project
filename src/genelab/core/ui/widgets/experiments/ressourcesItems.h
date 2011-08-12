#ifndef RESSOURCESITEMS_H
#define RESSOURCESITEMS_H

#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QVariantMap>
#include <ressources/ressourcesmanager.h>
#include "result.h"
#include <QDebug>

namespace GeneCraftCore{

// TREE

class ExperimentTreeWidgetItem : public QTreeWidgetItem
{
public:

    ExperimentTreeWidgetItem(DataWrapper dataw, bool showRessourceLocation = false)
    {
        this->dataw = dataw;
        int i=0;

        // new experiment
        QDateTime date = QDateTime::fromString(dataw.data["dateOfCreation"].toString(),"yyyy-MM-dd hh:mm:ss");
        if(date.daysTo(QDateTime::currentDateTime()) < 7)
            setIcon(0,QIcon(":img/icons/new"));

        // id
        setText(i++,dataw.data["_id"].toString());

        // local / online
        if(showRessourceLocation) {

            if(dataw.r) {
                if(dataw.r->getLocation() == "online")
                    setText(i++,"yes");
                else
                    setText(i++,"no");
            }
            else
                setText(i++,"yes"); // ONLINE -> NO RESSOURCE... FIXME (WE CAN DO IT CLEANER)
        }

        // author
        setText(i++,dataw.data["author"].toString());

        // date of creation
        setText(i++,dataw.data["dateOfCreation"].toString());
    }

    DataWrapper dataw;
};

class WorldTreeWidgetItem : public QTreeWidgetItem
{
public:

    WorldTreeWidgetItem(DataWrapper dataw)
    {
        this->dataw = dataw;

        QVariantMap biome = dataw.data["biome"].toMap();
        QVariantMap scene = dataw.data["scene"].toMap();

        setText(0,dataw.data["name"].toString());
        setText(1,QString::number(biome["gravity"].toDouble()));
        setText(2,scene["type"].toString());
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
        setText(2, QString::number(r->getGenome().toMap()["origins"].toMap()["generation"].toInt()));
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
