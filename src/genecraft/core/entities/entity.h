/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include "genecraftcoreclasses.h"
#include "statistics/statisticsstorage.h"
#include "body/fixation.h"
#include "brain/brainfunctional.h"

namespace GeneCraftCore {


/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Entities represent the "living" organisms simulate in GeneCraft.
 *
 * Entities are manage by the entitiesEngine.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class Entity : public QObject
{

public:

    Entity(QString name, QString family, QString type, int generation, QObject *parent = 0);

    ~Entity();

    // Origins
    const QString &getName() { return name; }
    void setName(QString name) {this->name = name;}
    const QString &getFamily() { return family; }
    void setFamily(QString family) { this->family = family; }
    const QString &getType() { return type; }
    void setType(QString type) { this->type = type; }
    int getGeneration() { return generation; }
    void setGeneration(int gen) { this->generation = gen; }

    // Shape
    TreeShape* getShape();
    void setShape(TreeShape* shape);

    // Sensors links
    void addLinkToSensor(Sensor *sensor);
    void removeLinksToSensor(Sensor *sensor);
    QList<Sensor *> &getSensors() { return sensors;  }

    // Effectors links
    void addLinkToEffector(Effector *effector);
    void removeLinksToEffector(Effector *effector);
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
    //static EntityPropertiesController *getInspectorWidget(Entity * selectedEntity = NULL, btRigidBody *selectedBody = NULL);

    // serialisation
    QVariant serialize();
    QVariant serializeOrigins();

    // Set ressource
    void setRessource(Ressource* r);
    Ressource* getRessource() { return r; }

    // Statistics
    StatisticsStorage * getStatisticsStorage() { return statisticsStorage; }
    void updadeStatistics();
    Statistic* getStatisticByName(QString statisticName);
    void updateStatisticByName(QString statisticName);
    QMap<QString, StatisticsProvider *> getStatistics() { return stats; }


    static const QString genomeVersion;

    virtual void setup();

    Statistic* getBrainActivityStat() {
        return this->brainActivityStat;
    }

    int getAge() {
        return age;
    }

    void setAge(int age);

    void incrAge();

    void addOutScript(int age, MotorFrom from);

    void setOutFromAge();

    bool isAlive();

protected:

    // Origins
    QString name;
    QString family;
    QString type;
    int generation;

    // Age
    int age;

    // Shape
    TreeShape* treeShape;

    // Brain
    QList<Sensor *> sensors;
    QList<Effector *> effectors;
    BrainFunctional *brain;
    Ressource* r;

    // Statistics
    QMap<QString, StatisticsProvider *> stats;
    Statistic*         brainActivityStat;
    Statistic*         ageStat;

    StatisticsStorage *statisticsStorage;

    // Scripting
    QMap<int, MotorFrom> outsFromScripts;


private:

    void setToMinimalOuts(Bone *bone);

};
}

#endif // ENTITY_H
