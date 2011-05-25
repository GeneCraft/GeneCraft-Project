#include "entity.h"
#include <QDebug>
#include "fixation.h"

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
        if(rootFix != NULL)
            rootFix->setup();
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
}
