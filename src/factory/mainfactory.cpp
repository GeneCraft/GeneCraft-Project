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

    // V�rifie que les d�pendances sont assur�es
    bool isValid();

    // Dernier message d'erreur
    QString error();

}
