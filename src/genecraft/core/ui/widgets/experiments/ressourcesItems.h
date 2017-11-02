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

#ifndef RESSOURCESITEMS_H
#define RESSOURCESITEMS_H

#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QTableWidgetItem>
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

        int daysToNow = date.daysTo(QDateTime::currentDateTime());
        if(daysToNow < 7)
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

        QString days;
        if(daysToNow < 1)
            days = "Today";
        else if(daysToNow > 2)
            days = QString::number(daysToNow) + " days ago";
        else
            days = QString::number(daysToNow) + " day ago";

        // date of creation
        setText(i++,days);
    }

    DataWrapper dataw;
};

class WorldTreeWidgetItem : public QTreeWidgetItem
{
public:

    WorldTreeWidgetItem(DataWrapper dataw)
    {
        this->dataw = dataw;

        QJsonObject biome = dataw.data["biome"].toObject();
        QJsonObject scene = dataw.data["scene"].toObject();

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

        setText(0, QString::number(r->getFitness(), 10, 4));
        setText(1, r->getWorker());
        setText(2, QString::number(r->getGenome()["origins"].toObject()["generation"].toInt()));
    }

    bool operator<(const QTreeWidgetItem &other)const {
        int column = treeWidget()->sortColumn();
        if(column == 0) {
            // sorting by fitness
            return text(0).toDouble() < other.text(0).toDouble();
        }
        else if(column == 2) {
            return text(2).toInt() < other.text(2).toInt();
        }
        else
            return text(column).toLower() < other.text(column).toLower();
    }

    Result * r;
};

class EntityTreeWidgetItem : public QTreeWidgetItem
{
public:

    EntityTreeWidgetItem(DataWrapper dataw)
    {
        this->dataw = dataw;

        QJsonObject origins = dataw.data["origins"].toObject();

        if(dataw.data.contains("_id")) {
            origins["name"] = dataw.data["_id"];
        }

        setText(0,origins["name"].toString());
        setText(1,origins["family"].toString());
        setText(2,origins["generation"].toString());
    }

    EntityTreeWidgetItem(QJsonObject genomeMap)
    {
        dataw.data = genomeMap;
        dataw.r = NULL;

        QJsonObject origins = dataw.data["origins"].toObject();

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
