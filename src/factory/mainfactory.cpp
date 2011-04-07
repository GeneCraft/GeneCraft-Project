#include "mainfactory.h"


namespace GeneLabFactory {

    MainFactory::MainFactory(QObject *parent) :
        QObject(parent)
    {
    }

    bool create(Ressource r);

    QMap<QString, GeneLabCore::Engine*>        getEngines();
    QMap<QString, GeneLabCore::EntityFamily*>  getFamilys();
    QMap<QString, GeneLabCore::World*>         getWorlds();

    // Vérifie que les dépendances sont assurées
    bool isValid();

    // Dernier message d'erreur
    QString error();

}
