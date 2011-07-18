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

//#include "statistics/fixdistancestat.h"
//#include "statistics/entityweightstat.h"
//#include "statistics/entityheightstat.h"
//#include "statistics/fixaveragevelocitystat.h"
//#include "statistics/entitytotalbonesstat.h"
//#include "statistics/fixdistancefromoriginstat.h"
//#include "statistics/entitytotalboneslengthstat.h"

namespace GeneLabCore {

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
        this->stats.insert("FixationStats", new FixationStats(statisticsStorage,treeShape->getRoot(),"Root"));
        this->brainActivityStat = statisticsStorage->registerStat("Brain Activity", "a / step");
    }
}

Entity::~Entity() {
    delete this->treeShape;
    delete this->brain;
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
            sensor->getInputs()[i]->connectTo(Tools::random(0.0, 1.0),
                                              Tools::random(0.0, 1.0),
                                              Tools::random(-1.0, 1.0));
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
            QString randomFunc = brain->createRandomFunc(1);
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

}
