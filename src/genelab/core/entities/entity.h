#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include "genelabcoreclasses.h"

namespace GeneLabCore {
    class Entity : public QObject
    {
        Q_OBJECT

    public:
        explicit Entity(QString name, QString family, int generation, QObject *parent = 0);
        ~Entity();

        inline const QString &getName() { return name; }

   //     static CreaturePropertiesController *getInspectorWidget(Creature * selectedCreature = 0, btRigidBody *selectedBody = 0);

        inline void setRootFixation(Fixation *rootFix) { this->rootFix = rootFix; }
        inline Fixation *getRootFixation() { return rootFix; }

        /*
        Shape* getShape();
        void   setShape(Shape*);
        void print();
        */

    signals:

    public slots:
        virtual void setup();

    protected:

        // shape root
        Fixation *rootFix;

        // entity
        QString name;
        QString family;
        int generation;

    };
}

#endif // ENTITY_H
