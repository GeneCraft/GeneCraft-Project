#include "genericfamily.h"

#include "entity.h"
#include "treeshape.h"
#include "fixation.h"
#include "brainfunctional.h"
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
    // Brain
    entity->setBrain(new BrainFunctional(entityMap.value("brain")));

    // Body
    QVariantMap body = entityMap.value("body").toMap();
    if(body.value("shapeType").toString().compare(QString("TreeShape")) == 0)
    {
        TreeShape* treeShape = new TreeShape(shapesFactory);

        btTransform initTransform;
        initTransform.setIdentity();
        initTransform.setOrigin(initialPosition);

        treeShape->createRootFromGenotype(body.value("shape"), initTransform);
        entity->setShape(treeShape);
        treeShape->buildFixFromGenotype(treeShape->getRoot(),body.value("shape").toMap().value("rootFix"));
    }


    return entity;
}


Entity *GenericFamily::createViginEntity(btShapesFactory *shapesFactory,
                                                btScalar rootFixRadius,
                                                const btVector3 &initialPosition)
{
    Entity * entity = new Entity("no name", "no family", 0);
    entity->setBrain(new BrainFunctional(10));

    TreeShape *shape = new TreeShape(shapesFactory);

    btTransform initTransform;
    initTransform.setIdentity();
    initTransform.setOrigin(initialPosition);

    shape->setRoot(new Fixation(shapesFactory,rootFixRadius,initTransform));
    entity->setShape(shape);

    return entity;
}
}
