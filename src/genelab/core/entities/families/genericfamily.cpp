#include "genericfamily.h"

#include "entity.h"
#include "treeshape.h"
#include <QDebug>

namespace GeneLabCore {
GenericFamily::GenericFamily()
{
}

Entity *GenericFamily::createEntity(QVariant genotype,
                                    btShapesFactory *shapesFactory,
                                    const btVector3 &initialPosition)
{
    QVariantMap entityMap = genotype.toMap();

    // Entity & origins
    QVariantMap origins = entityMap.value("origins").toMap();
    Entity * entity = new Entity(origins.value("name").toString(),
                                  origins.value("family").toString()
                                  ,0);

    // Body
    QVariantMap body = entityMap.value("body").toMap();
    if(body.value("shapeType").toString().compare(QString("TreeShape")) == 0)
    {
        btTransform initTransform;
        initTransform.setIdentity();
        initTransform.setOrigin(initialPosition);
        entity->setShape(new TreeShape(shapesFactory,body.value("shape"),initTransform));
    }

    // Brain
    // entity->setBrain(new Brain(entityMap.value("brain")))

    return entity;
}
}
