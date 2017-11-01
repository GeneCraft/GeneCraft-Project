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

#ifndef TERRAIN_H
#define TERRAIN_H

#include "genecraftcoreclasses.h"

#include "engine.h"
#include "entities/entitiesengine.h"
#include <QObject>
#include <QJsonObject>

namespace GeneCraftCore {

    /**
     * @brief The usefull informations about a dynamic terrain
     *
     */
    class TerrainData {
    public:
        /**
         * @brief The type of the terrain, we have different shape of dynamic field
         NoFloor     : no dynamic field
         FlatLand    : a basic flat land
         RandomBoxes : random flat boxes
         StairsUp    : random boxes creating a stair up in all directions
         StairsDown  : random boxes creating a stair down in all directions
         Slope       : a basic flat Slope of %degree
         *
         */
        enum FloorType { NoFloor, FlatLand, RandomBoxes, StairsUp, StairsDown, Slope };
        FloorType floor; /**< the type of the field */
        QJsonObject floorData; /**< the configurations informations from the field */

        /**
         * @brief simple comparator, return true if the field is of the same type
         and have the same configuration
         *
         * @param t
         * @return bool operator
         */
        bool operator==(const TerrainData& t) {
            return this->floor == t.floor && this->floorData == t.floorData;
        }

        QMap<QString, btBox*> blocs; /**< The list of created boxes */
        float width; /**< the width of a box of the field */
        float height; /**< the incremental height of boxes on the field */
        float randomHeight; /**< the randomness of boxes height */

    };

    /**
     * @brief The engine that manage dynamics fields arround creatures.
     In a "infinite" world, the field has to be generated arround creatures this
     is a temporary workarround to allow thoses kind of dynamic world arround creatures
     WARNING: does not work on multiples worlds!
     *
     */
    class Terrain : public Engine
    {
    public:
        /**
         * @brief Create the terrain engine, it'll need entities engines to
         create world under the actives entity
         *
         * @param ee
         * @param parent
         */
        explicit Terrain(EntitiesEngine* ee, QObject* parent = 0);
        /**
         * @brief The engine will add new boxes before all steps accordingly to
         entity positions
         *
         */
        virtual void beforeStep(); // Adding new boxes !

        /**
         * @brief Add a field to the engine
         *
         * @param floorData
         */
        TerrainData* addTerrain(QJsonObject floorData);
        /**
         * @brief Remove a field from the engine
         *
         * @param
         */
        void removeTerrain(TerrainData*);

        /**
         * @brief Set the shapesFactory used to create boxes
         *
         * @param factory
         */
        void setShapesFactory(btShapesFactory* factory) {
            this->factory = factory;
        }

    protected:
        QList<TerrainData*> terrains; /**< the list of terrains */
        EntitiesEngine* ee; /**< the entity engine */
        btShapesFactory* factory; /**< the shapesfactory */

    };

}

#endif // TERRAIN_H
