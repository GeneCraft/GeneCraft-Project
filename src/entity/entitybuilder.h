#ifndef ENTITYBUILDER_H
#define ENTITYBUILDER_H

#include <QObject>
#include "struct/shapebuilder.h"
#include "entity.h"

class EntityBuilder : public QObject
{
    Q_OBJECT
public:
    explicit EntityBuilder(QObject *parent = 0);
    virtual  Entity* build() = 0;

signals:

public slots:

private:
    ShapeBuilder* shapeBuilder;

};

#endif // ENTITYBUILDER_H
