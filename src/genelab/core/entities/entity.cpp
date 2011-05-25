#include "entity.h"
#include <QDebug>
#include "fixation.h"

namespace GeneLabCore {

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
}
