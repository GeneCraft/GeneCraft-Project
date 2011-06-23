#ifndef MAINFACTORY_H
#define MAINFACTORY_H

#include <QObject>
#include <QMap>
#include "genelabcoreclasses.h"

namespace GeneLabCore {
    class MainFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit MainFactory(QWidget* sceneWidget, unsigned long winId, QObject *parent = 0);

        bool create(Ressource* r);

        QMap<QString, Engine*>        getEngines();
        QMap<QString, QWidget*>       getWidgets();
        btShapesFactory *             getShapesFactory();

        // Vérifie que les dépendances sont assurées
        bool isValid();

        // Dernier message d'erreur
        QString error();

    signals:

    public slots:

    private:
        QMap<QString, Engine*>         engines;
        QMap<QString, QWidget*>        widgets;
        btShapesFactory *              shapesFactory;

    };

}

#endif // MAINFACTORY_H
