#ifndef MAINFACTORY_H
#define MAINFACTORY_H

#include <QObject>
#include <QMap>
#include "classes.h"

namespace GeneLabFactory {

    class MainFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit MainFactory(QWidget* sceneWidget, unsigned long winId, QObject *parent = 0);

        bool create(Ressource r);

        QMap<QString, GeneLabCore::Engine*>        getEngines();
        QMap<QString, GeneLabCore::EntityFamily*>  getFamilys();
        QMap<QString, GeneLabCore::World*>         getWorlds();
        QMap<QString, QWidget*>                    getWidgets();

        // V�rifie que les d�pendances sont assur�es
        bool isValid();

        // Dernier message d'erreur
        QString error();

    signals:

    public slots:

    private:
        QMap<QString, GeneLabCore::Engine*>         engines;
        QMap<QString, GeneLabCore::EntityFamily*>   familys;
        QMap<QString, GeneLabCore::World*>          worlds;
        QMap<QString, QWidget*>                     widgets;

    };

}

#endif // MAINFACTORY_H