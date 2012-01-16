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

#include "entity.h"
#include "body/fixation.h"
#include "body/treeshape.h"
#include "brain/brainfunctional.h"
#include "brain/brainin.h"

#include "brain/brainpluggrid.h"
#include "brain/brainout.h"
#include "sensors/sensor.h"
#include "effectors/effector.h"

#include "ressources/ressource.h"
#include "body/bone.h"
#include "tools.h"

// Statistics
#include "statistics/statisticsprovider.h"
#include "statistics/statisticsstorage.h"
#include "statistics/treeshapestats.h"
#include "statistics/fixationstats.h"

namespace GeneCraftCore {

    const QString Entity::genomeVersion = "0.1";
//EntityPropertiesController* Entity::inspectorWidget = NULL;

Entity::Entity(QString name, QString family, QString type, int generation, QObject *parent) :
    QObject(parent), r(NULL)
{
    this->name          = name;
    this->family        = family;
    this->generation    = generation;
    this->type          = type;
    this->statisticsStorage = new StatisticsStorage();

}

void Entity::setup() {

    if(treeShape) {
        this->treeShape->setup();

        this->stats.insert("TreeShapeStats", new TreeShapeStats(statisticsStorage,treeShape));
        this->stats.insert("FixationStats", new FixationStats(statisticsStorage,treeShape->getRoot(),"root"));
        this->brainActivityStat = statisticsStorage->registerStat("brainActivity", "a / step");
        this->ageStat = statisticsStorage->registerStat("age", "step");

        // BRAIN MODIF TRY
        //this->brainPlugGridSizeStat = statisticsStorage->registerStat("brainPlugGridSize", "edge size");
        //this->brainPlugGridSizeStat->setValue(brain->getPlugGrid()->getSize());
        //this->brainPlugGridSizeStat->setResetable(false);
    }
}

Entity::~Entity() {
    delete this->statisticsStorage;
    foreach(StatisticsProvider* stat, stats) {
        delete stat;
    }

    stats.clear();

    delete this->treeShape;
    delete this->brain;

    if(r)
        delete this->r;
}

TreeShape* Entity::getShape() {
    return this->treeShape;
}

void Entity::setShape(TreeShape* shape) {
    this->treeShape = shape;
    if(this->treeShape->getRoot() != NULL)
        this->treeShape->getRoot()->setEntity(this);
}

QVariant Entity::serializeOrigins()
{
    QVariantMap origins;

    origins.insert("name",name);
    origins.insert("family",family);
    origins.insert("generation",generation);

    return origins;
}

QVariant Entity::serialize()
{
    QVariantMap entityVariant;

    entityVariant.insert("version", genomeVersion);
    entityVariant.insert("type", type);

    entityVariant.insert("origins",serializeOrigins());
    entityVariant.insert("brain",brain->serialize());
    entityVariant.insert("body",treeShape->serialize());

    return entityVariant;
}

// Sensors links
void Entity::addLinkToSensor(Sensor *sensor) {
    sensors.append(sensor);

    // Inputs connections to grid
    for(int i = 0; i < sensor->getInputs().size(); i++) {
        if(sensor->getInputs()[i]->getConnexions().size() == 0) {
            sensor->getInputs()[i]->connectRandomly();
        }
        brain->getPlugGrid()->connectInput(sensor->getInputs()[i]);
    }
}

void Entity::removeLinksToSensor(Sensor *sensor) {

    sensors.removeAll(sensor);

    // Inputs connections to grid
    for(int i = 0; i < sensor->getInputs().size(); i++) {
        sensor->getInputs()[i]->disconnectTotally();
        brain->getPlugGrid()->disconnectInput(sensor->getInputs()[i]);
    }
}

// Modifiers links
void Entity::addLinkToEffector(Effector *modifier) {
    effectors.append(modifier);

    // Outputs connections to grid
    for(int i = 0; i < modifier->getOutputs().size(); i++) {
        // No connexion is not an option, at least a one depth tree !
        // But should not happend that often, except when creating
        // Creatures from creature viewer
        if(modifier->getOutputs()[i]->getConnexionInfo() == "") {
            QString randomFunc = brain->createRandomFunc(2);
            modifier->getOutputs()[i]->setConnexionInfo(QVariant(randomFunc));
        }

        brain->addOut(modifier->getOutputs()[i]);
    }
}

void Entity::removeLinksToEffector(Effector *effector) {
    effectors.removeAll(effector);
}

void Entity::addBrainOut(BrainOut *brainOut)
{

    if(brainOut->getConnexionInfo() == "") {
        QString randomFunc = brain->createRandomFunc(2);
        brainOut->setConnexionInfo(QVariant(randomFunc));
    }

    brain->addOut(brainOut);
}

void Entity::removeBrainOut(BrainOut *brainOut) {
    brain->removeOut(brainOut);
}

void Entity::setRessource(Ressource* r) {
    this->r = r;
}

void Entity::setToMinimalOuts(Bone *bone)
{
    bone->setToMinimalOuts();

    foreach(Bone *b,bone->getEndFixation()->getBones())
        setToMinimalOuts(b);
}

void Entity::setToMinimalOuts()
{
    foreach(Bone *b,treeShape->getRoot()->getBones())
        setToMinimalOuts(b);
}

void Entity::updadeStatistics(){

    foreach(StatisticsProvider * s, stats)
        s->step();
}

Statistic* Entity::getStatisticByName(QString statisticName)
{
    if(!this->statisticsStorage->exists(statisticName))
        return NULL;

    return this->statisticsStorage->getStatistics().find(statisticName).value();
}

void Entity::updateStatisticByName(QString statisticName)
{
    if(stats.contains(statisticName))
        stats.value(statisticName)->step();
}

bool Entity::isAlive() {
    return this->treeShape->getRoot()->isInOnePiece();
}

void Entity::setOutFromAge() {
    if(this->outsFromScripts.contains(this->age)) {

        foreach(Statistic* s, this->statisticsStorage->getStatistics()) {
            s->resetAll();
        }

        qDebug() << "changement d'out par scripting d'entite." << outsFromScripts[this->age];
        this->treeShape->getRoot()->setOutputsFrom(outsFromScripts[this->age]);
        this->outsFromScripts.remove(this->age);


        this->setAge(0);

    }
}

void Entity::setAge(int age) {
    this->age = age;
    this->setOutFromAge();
    this->ageStat->resetAll();
    this->ageStat->setValue(age);
}

void Entity::incrAge() {
    this->age++;
    this->setOutFromAge();
    this->ageStat->setValue(1);
}

void Entity::addOutScript(int age, MotorFrom from) {
    qDebug() << age << from;
    if(this->outsFromScripts.contains(age)) {
        this->outsFromScripts.remove(age);
    }
    this->outsFromScripts.insert(age, from);
}

}
