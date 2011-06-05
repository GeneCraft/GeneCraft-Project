#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include "genelabcoreclasses.h"
#include "widgets/entities/entitypropertiescontroller.h"
#include "brain/brainfunctional.h"

namespace GeneLabCore {
    class Entity : public QObject
    {
        Q_OBJECT

    public:

        Entity(QString name, QString family, int generation, QObject *parent = 0);

        ~Entity();

        // Origins
        const QString &getName() { return name; }
        const QString &getFamily() { return family; }

        // Shape
        TreeShape* getShape();
        void setShape(TreeShape* shape);

        // Sensors links
        void addLinkToSensor(Sensor *sensor);
        QList<Sensor *> &getSensors() { return sensors;  }

        // Modifiers links
        void addLinkToModifier(Modifier *modifier);
        QList<Modifier *> &getModifiers() { return modifiers;  }

        // Brain
        void setBrain(BrainFunctional* brain) { this->brain = brain; }
        Brain *getBrain() { return brain; }

        // Qt Render
        static EntityPropertiesController *getInspectorWidget(Entity * selectedEntity = NULL, btRigidBody *selectedBody = NULL);

        // serialisation
        QVariant serialize();
        QVariant serializeOrigins();

    signals:

    public slots:
        virtual void setup();

    protected:

        // Origins
        QString name;
        QString family;
        int generation;

        // Shape
        TreeShape* treeShape;

        // Brain
        QList<Sensor *> sensors;
        QList<Modifier *> modifiers;
        BrainFunctional *brain;

        // Qt Render
        static EntityPropertiesController *inspectorWidget;

    };
}

#endif // ENTITY_H
