#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include "struct/shape.h"

class Entity : public QObject
{
    Q_OBJECT
public:
    explicit Entity(QObject *parent = 0);

signals:

public slots:

private:
    Shape structure;

};

#endif // ENTITY_H
