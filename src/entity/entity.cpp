#include "entity.h"
#include <QDebug>

namespace GeneLabCore {
    Entity::Entity(QString name, QString family, int generation, QObject *parent) :
        QObject(parent)
    {
        this->name = name;
        this->family = family;
        this->generation = generation;
    }

    void Entity::setup() {

    }

    Entity::~Entity() {

    }
}
