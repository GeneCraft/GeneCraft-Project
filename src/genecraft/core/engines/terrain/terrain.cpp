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

#include "terrain.h"
#include "entities/body/treeshape.h"
#include "entities/body/fixation.h"
#include "btBulletDynamicsCommon.h"
#include "btshapesfactory.h"
#include "bullet/shapes/btbox.h"

#include "tools.h"

#include <QStringList>
#define TERRAIN_WIDTH 5
namespace GeneCraftCore {
    Terrain::Terrain(EntitiesEngine* ee, QObject* parent) : Engine(parent)
    {
        this->ee = ee;
    }

    void Terrain::beforeStep() {
        static int cpt = 0;
        cpt++;
        if(cpt%10) {
            return;
        }

        foreach(TerrainData* terrain, terrains) {
            switch(terrain->floor) {
            case TerrainData::NoFloor:
            case TerrainData::FlatLand:
            case TerrainData::Slope:
                // Nothing to do
                break;

            case TerrainData::RandomBoxes:
            case TerrainData::StairsUp:
            case TerrainData::StairsDown:
                QSet<QString> neededs;


                // Check wich blocs need to be added
                foreach(Entity* e, ee->getAllEntities()) {
                    // Get entity bounding box
                    TreeShape* s = e->getShape();
                    Fixation* f  = s->getRoot();
                    btTransform t = f->getRigidBody()->getWorldTransform();
                    float x, y;
                    x = floor(t.getOrigin().getX()/terrain->width);
                    y = floor(t.getOrigin().getZ()/terrain->width);
                    for(int i = -TERRAIN_WIDTH; i <= TERRAIN_WIDTH; i++) {
                        for(int j = -TERRAIN_WIDTH; j <= TERRAIN_WIDTH; j++) {
                            neededs.insert(QString::number(x+i)+"_"+QString::number(y+j));
                        }
                    }
                }

                // Clean already present blocs and delete others
                QList<QString> keys = terrain->blocs.keys();
                foreach(QString existant, keys) {
                    if(!neededs.contains(existant)) {

                        delete terrain->blocs[existant];
                        terrain->blocs.remove(existant);
                    } else {
                        neededs.remove(existant);
                    }
                }
                // Create the new blocs
                foreach(QString needed, neededs) {
                    QStringList x_y = needed.split("_");
                    float x = x_y[0].toFloat();
                    float z = x_y[1].toFloat();

                    float y = 1;

                    float dist = sqrt(x*x+z*z);

                    // Compute the y composante
                    switch(terrain->floor) {
                    case TerrainData::RandomBoxes:
                        y = terrain->height + Tools::random(0., terrain->randomHeight);
                        break;
                    case TerrainData::StairsDown:
                        y = terrain->height*-dist + Tools::random(0., terrain->randomHeight);
                        break;
                    case TerrainData::StairsUp:
                        y =1*terrain->height*dist - Tools::random(0., terrain->randomHeight);
                        break;
                    default:
                        // Should not happend!
                        break;
                    }

                    btVector3 size(terrain->width, terrain->height + terrain->randomHeight, terrain->width);

                    btVector3 pos(x*terrain->width,
                                  y,
                                  z*terrain->width);


                    btTransform position;
                    position.setIdentity();
                    position.setOrigin(pos);

                    terrain->blocs.insert(needed, factory->createBox(size,
                                                                    position,
                                                                    0,
                                                                    terrain->floorData));
                    terrain->blocs[needed]->setup();
                }


                break;
            }
        }
    }

    TerrainData* Terrain::addTerrain(QVariantMap floorData) {
        TerrainData* terrain = new TerrainData();
        terrain->floorData = floorData;

        // Loading the type
        QString type = floorData["type"].toString();
        if(type == "nofloor") {
            terrain->floor = TerrainData::NoFloor;
        } else if (type == "flatland") {
            terrain->floor = TerrainData::FlatLand;
        } else if (type == "randomBoxes") {
            terrain->floor = TerrainData::RandomBoxes;
        } else if (type == "stairsUp") {
            terrain->floor = TerrainData::StairsUp;
        } else if (type == "stairsDown") {
            terrain->floor = TerrainData::StairsDown;
        } else if (type == "slope") {
            terrain->floor = TerrainData::Slope;
        }

        // Loading eventual step width
        if(floorData.contains("width")) {
            terrain->width = floorData["width"].toFloat();
        } else {
            terrain->width = 1;
        }

        // Loading eventual step height
        if(floorData.contains("minHeight")) {
            float minHeight = floorData["minHeight"].toFloat();
            float maxHeight = floorData["maxHeight"].toFloat();
            terrain->height = (minHeight + maxHeight) / 2.;
            terrain->randomHeight = maxHeight - minHeight;
        } else {
            terrain->height       = 1;
            terrain->randomHeight = 0;
        }

        terrain->width = 10;
        terrain->height = 1;
        terrain->randomHeight = 1;

        this->terrains.append(terrain);
        return terrain;
    }

    void Terrain::removeTerrain(TerrainData* terrain) {
        this->terrains.removeAll(terrain);
        delete terrain;
    }
}
