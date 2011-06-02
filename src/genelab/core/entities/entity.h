#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include "genelabcoreclasses.h"
#include "entitypropertiescontroller.h"

namespace GeneLabCore {
    class Entity : public QObject
    {
        Q_OBJECT

    public:
        explicit Entity(QString name, QString family, int generation, QObject *parent = 0);
        ~Entity();

        // Origins
        inline const QString &getName() { return name; }
        inline const QString &getFamily() { return family; }

        // Shape
        TreeShape* getShape();
        void setShape(TreeShape* shape);

        // Sensors links
        inline void addLinkToSensor(Sensor *sensor) { sensors.append(sensor); }
        inline QList<Sensor *> &getSensors() { return sensors;  }

        // Modifiers links
        inline void addLinkToModifier(Modifier *modifier) { modifiers.append(modifier); }
        inline QList<Modifier *> &getModifiers() { return modifiers;  }

        // Brain
        inline Brain *getBrain() { return brain; }

        // Qt Render
        static EntityPropertiesController *getInspectorWidget(Entity * selectedEntity = NULL, btRigidBody *selectedBody = NULL);

        // serialisation
        QVariant serialize();

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
        Brain *brain;

        // Qt Render
        static EntityPropertiesController *inspectorWidget;

    };
}

#endif // ENTITY_H
