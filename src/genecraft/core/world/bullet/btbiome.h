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

#ifndef BTBIOME_H
#define BTBIOME_H

#include <QObject>
#include <QVariant>

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "btfactory.h"
#include "btworld.h"

namespace GeneCraftCore {

class btBiome : public QObject
{
public:
    explicit btBiome(btWorld* world, QVariant biomeData, QObject *parent = 0);
    ~btBiome();

    virtual void setup();

    virtual void setBulletWorld(btDynamicsWorld* world) {
        this->world = world;
    }

protected:
    QVariantMap data;

    btDynamicsWorld* world;

    btWorld* bulletWorld;
};

}

#endif // BTBIOME_H
