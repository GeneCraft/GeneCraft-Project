#include "entity.h"
#include <QDebug>

namespace GeneLabCore {
    Entity::Entity(QString name, QString family, int generation, QObject *parent) :
        QObject(parent)
    {
        this->name = name;
        this->family = family;
        this->generation = generation;
        this->shape = NULL;
    }

    void Entity::setup() {

    }

    Entity::~Entity() {
        delete this->shape;
    }


    void Entity::setShape(Shape *s) {
        this->shape = s;
    }

    Shape* Entity::getShape() {
        return this->shape;
    }

    void Entity::print() {
        if(shape != NULL) {
            qDebug() << "Entite " << name << " family " << family;
            qDebug() << "Generation " << generation;
            shape->print();
        }
    }
}
