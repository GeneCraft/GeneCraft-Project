#include "creaturefactory.h"
#include "genome/genomebuilder.h"
#include "families/genericfamily.h"
#include "entity.h"

namespace GeneCraftCore {

    Entity* CreatureFactory::createEntity(QVariant data,
                                          btShapesFactory* shapesFactory,
                                          btVector3 position) {
        QVariantMap entityData = data.toMap();

        // inside a result ?
        if(entityData["type"].toString() == "result") {
            // Decapsulate
            qDebug() << "decapsulation from result !";
            entityData = entityData["genome"].toMap();
        }

        // Version check
        if(entityData["version"].toString() != Entity::genomeVersion) {
            //error = "Version de genome anterieur au logiciel actuel";
            //qDebug() << error;

            // Maybe conversion if possible

            // else
            return NULL;
        }

        // Generic entity
        if(entityData["type"].toString() == "generic")
            return GenomeBuilder::buildEntity(entityData, shapesFactory, position);
        // Whatever
        else if(entityData["type"].toString() == "symetric")
            return GenomeBuilder::buildEntity(entityData, shapesFactory, position);
        // Whatever else
        return NULL;
    }
}
