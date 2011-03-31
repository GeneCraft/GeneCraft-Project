#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include "struct/shape.h"
#include "struct/shapebuilder.h"

namespace GeneLabCore {
    class Entity : public QObject
    {
        Q_OBJECT

    public:
        explicit Entity(QString name, QString family, int generation, QObject *parent = 0);
        ~Entity();
        Shape* getShape();
        void   setShape(Shape*);

        void print();

    signals:

    public slots:
        void setup();

    private:
        Shape* shape;
        QString name;
        QString family;
        int generation;

    };
}

#endif // ENTITY_H
