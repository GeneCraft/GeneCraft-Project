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

#include "btbiome.h"
#include "btworld.h"

namespace GeneCraftCore {
    btBiome::btBiome(btWorld* world, QVariant biomeData, QObject *parent) :
        QObject(parent)
    {
        world->setBiome(this);
        this->data = biomeData.toMap();
    }

    btBiome::~btBiome() {

    }

    void btBiome::setup() {
        btScalar gravity = data["gravity"].toFloat();
        world->setGravity(btVector3(0,-gravity,0));
    }

}
