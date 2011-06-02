#include "entity.h"
#include <QDebug>
#include "fixation.h"
#include "treeshape.h"
#include "brainfunctional.h"

namespace GeneLabCore {

    EntityPropertiesController* Entity::inspectorWidget = NULL;

    Entity::Entity(QString name, QString family, int generation, QObject *parent) :
        QObject(parent)
    {
        this->name          = name;
        this->family        = family;
        this->generation    = generation;
    }

    void Entity::setup() {
        this->treeShape->setup();
    }

    Entity::~Entity() {
    }

    EntityPropertiesController *Entity::getInspectorWidget(Entity * selectedCreature, btRigidBody *selectedBody)
    {
        if(inspectorWidget == NULL)
            inspectorWidget = new EntityPropertiesController();

        if(selectedCreature != NULL)
            inspectorWidget->setEntity(selectedCreature,selectedBody);

        return inspectorWidget;
    }


    TreeShape* Entity::getShape() {
        return this->treeShape;
    }

    void Entity::setShape(TreeShape* shape) {
        this->treeShape = shape;
        this->treeShape->getRoot()->setEntity(this);
    }

    QVariant Entity::serialize()
    {
        QVariantMap entityVariant;

        //entityVariant.insert("origins",serializeOrigins());
        //entityVariant.insert("brain",brain->serialize());
        entityVariant.insert("body",treeShape->serialize());

        return entityVariant;
    }
}
