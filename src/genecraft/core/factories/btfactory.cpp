#include "btfactory.h"

// Qt
#include <QDebug>
#include <QVBoxLayout>

#include "bullet/bulletengine.h"
#include "ressources/ressource.h"

#include "entities/entitiesengine.h"

#include "terrain/terrain.h"
namespace GeneCraftCore {

btFactory::btFactory(QObject *parent) :
    QObject(parent)
{
    // ----------------------
    // -- Physics : Bullet --
    // ----------------------
    qDebug() << "Init Bullet";
    BulletEngine* bulletEngine = new BulletEngine();
    this->engines.insert("Bullet", bulletEngine);
    qDebug() << "[OK]\n";

    // ---------------------
    // -- Entities engine --
    // ---------------------
    qDebug() << "Init Entities Engine";
    EntitiesEngine* entitiesEngine = new EntitiesEngine();
    this->engines.insert("Entities", entitiesEngine);
    qDebug() << "[OK]\n";

    // Terrain engine
    qDebug() << "Init Terrain Engine";
    Terrain* terrain = new Terrain(entitiesEngine);
    this->engines.insert("Terrain", terrain);
    qDebug() << "[OK]";
}


QMap<QString, Engine*> btFactory::getEngines() {
    return QMap<QString, Engine*>(engines);

}

QMap<QString, QWidget*> btFactory::getWidgets() {
    return widgets;
}

Engine *btFactory::getEngineByName(QString name)
{
    return engines.find(name).value();
}

}
