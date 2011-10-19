#ifndef TERRAIN_H
#define TERRAIN_H

#include "genecraftcoreclasses.h"

#include "engine.h"
#include "entities/entitiesengine.h"
#include <QObject>
#include <QVariant>

namespace GeneCraftCore {

    class TerrainData {
    public:
        enum FloorType { NoFloor, FlatLand, RandomBoxes, StairsUp, StairsDown, Slope };
        FloorType floor;
        QVariantMap floorData;

        bool operator==(const TerrainData& t) {
            return this->floor == t.floor && this->floorData == t.floorData;
        }

        QMap<QString, btBox*> blocs;
        float width;
        float height;
        float randomHeight;

    };

    class Terrain : public Engine
    {
    public:
        explicit Terrain(EntitiesEngine* ee, QObject* parent = 0);
        virtual void beforeStep(); // Adding new boxes !

        TerrainData* addTerrain(QVariantMap floorData);
        void removeTerrain(TerrainData*);

        void setShapesFactory(btShapesFactory* factory) {
            this->factory = factory;
        }

    protected:
        QList<TerrainData*> terrains;
        EntitiesEngine* ee;
        btShapesFactory* factory;

    };

}

#endif // TERRAIN_H
