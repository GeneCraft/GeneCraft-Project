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

#include "btfactory.h"

// Qt
#include <QDebug>

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
