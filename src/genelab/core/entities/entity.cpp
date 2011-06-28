#include "entity.h"
#include <QDebug>
#include "body/fixation.h"
#include "body/treeshape.h"
#include "brain/brainfunctional.h"
#include "brain/brainin.h"

#include "brain/brainpluggrid.h"
#include "brain/brainout.h"
#include "sensors/sensor.h"
#include "modifiers/modifier.h"

#include "ressources/ressource.h"

namespace GeneLabCore {

    EntityPropertiesController* Entity::inspectorWidget = NULL;

    Entity::Entity(QString name, QString family, int generation, QObject *parent) :
        QObject(parent), r(NULL)
    {
        this->name          = name;
        this->family        = family;
        this->generation    = generation;
    }

    void Entity::setup() {
        this->treeShape->setup();
    }

    Entity::~Entity() {
        delete this->treeShape;
        delete this->brain;
        delete this->r;
    }

    EntityPropertiesController *Entity::getInspectorWidget(Entity * selectedCreature, btRigidBody *selectedBody)
    {
        if(inspectorWidget == NULL)
            inspectorWidget = new EntityPropertiesController();

        if(selectedCreature != NULL)
            inspectorWidget->setEntity(selectedCreature,selectedBody);

        return inspectorWidget;
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

        return origins;
    }

    QVariant Entity::serialize()
    {
        QVariantMap entityVariant;

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
            // little cheat TODO ???
            for(int j = sensor->getInputs()[i]->getConnexions().size(); j < 2; j++) {
                sensor->getInputs()[i]->connectTo(((float)qrand())/RAND_MAX,        //  0.0 to 1.0
                                                  ((float)qrand())/RAND_MAX,        //  0.0 to 1.0
                                                  ((float)qrand())/RAND_MAX*2 -1);  // -1.0 to 1.0
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
            if(modifier->getOutputs()[i]->getConnexionInfo() == "") {
                QString randomFunc = brain->createRandomFunc(5);
                modifier->getOutputs()[i]->setConnexionInfo(QVariant(randomFunc));
            }

            brain->addOut(modifier->getOutputs()[i]);
        }
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
}
