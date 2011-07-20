#ifndef RESSOURCESITEMS_H
#define RESSOURCESITEMS_H

#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QVariantMap>
#include <ressources/ressourcesmanager.h>

namespace GeneLabCore{

// TREE

class ExperimentTreeWidgetItem : public QTreeWidgetItem
{
public:

    ExperimentTreeWidgetItem(DataWrapper dataw)
    {
        this->dataw = dataw;

        setText(0,dataw.data["id"].toString());
        setText(1,dataw.data["author"].toString());
        setText(2,dataw.data["dateOfCreation"].toString());
    }

    DataWrapper dataw;
};

class EntityTreeWidgetItem : public QTreeWidgetItem
{
public:

    EntityTreeWidgetItem(DataWrapper dataw)
    {
        this->dataw = dataw;

        QVariantMap origins = dataw.data["origins"].toMap();

        setText(0,origins["name"].toString());
        setText(1,origins["family"].toString());
        setText(2,origins["generation"].toString());
    }

    EntityTreeWidgetItem(QVariantMap genomeMap)
    {
        dataw.data = genomeMap;
        dataw.r = NULL;

        QVariantMap origins = dataw.data["origins"].toMap();

        setText(0,origins["name"].toString());
        setText(1,origins["family"].toString());
        setText(2,origins["generation"].toString());
    }

    DataWrapper dataw;
};

}

#endif // RESSOURCESITEMS_H
