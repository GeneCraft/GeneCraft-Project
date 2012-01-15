/*
Copyright 2011, 2012 Aur�lien Da Campo, Cyprien Huissoud

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

#ifndef BTOBIOME_H
#define BTOBIOME_H

#include "genecraftcoreclasses.h"
#include "btbiome.h"

namespace GeneCraftCore {

class btoBiome : public btBiome
{
public:
    explicit btoBiome(btoWorld* world, QVariant biomeData, QObject *parent = 0);

    virtual void setup();

    QVariantList getLightsData() { return lightsData; }
    void setLightsData(QVariantList lightsData) { this->lightsData = lightsData; }

private:
    btoWorld* world;

    QVariantList lightsData;
};

}

#endif // BTOBIOME_H
