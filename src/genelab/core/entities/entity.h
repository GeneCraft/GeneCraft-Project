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
        int getGeneration() { return generation; }

        // Shape
        TreeShape* getShape();
        void setShape(TreeShape* shape);

        // Sensors links
        void addLinkToSensor(Sensor *sensor);
        void removeLinksToSensor(Sensor *sensor);
        QList<Sensor *> &getSensors() { return sensors;  }

        // Effectors links
        void addLinkToEffector(Effector *effector);
        //void removeLinksToEffector(Effector *effector);
        void addBrainOut(BrainOut *brainOut);
        void removeBrainOut(BrainOut *brainOut);
        QList<Effector *> &getEffectors() { return effectors;  }

        // Brain
        void setBrain(BrainFunctional* brain) { this->brain = brain; }
        Brain *getBrain() { return brain; }

        /**
         * compute de minimal outs
         *
         * if a constraint is rigid (no free degrees), we can unplug outputs...
         */
        void setToMinimalOuts();

        // Qt Render
        static EntityPropertiesController *getInspectorWidget(Entity * selectedEntity = NULL, btRigidBody *selectedBody = NULL);

        // serialisation
        QVariant serialize();
        QVariant serializeOrigins();

        // Set ressource
        void setRessource(Ressource* r);
        Ressource* getRessource() { return r; }

        // Statistics
        void updadeStatistics();
        float getStatisitcByName(QString statisticName);
        void updateStatisticByName(QString statisticName);

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
        QList<Effector *> effectors;
        BrainFunctional *brain;
        Ressource* r;

        // Statistics
        QMap<QString, Statistic *> stats;

        // Qt Render
        static EntityPropertiesController *inspectorWidget;

    private:

        void setToMinimalOuts(Bone *bone);

    };
}

#endif // ENTITY_H
