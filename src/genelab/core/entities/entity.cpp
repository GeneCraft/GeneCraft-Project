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

namespace GeneLabCore {

    EntityPropertiesController* Entity::inspectorWidget = NULL;

    Entity::Entity(QString name, QString family, int generation, QObject *parent) :
        QObject(parent)
    {
        this->name          = name;
        this->family        = family;
        this->generation    = generation;
    }

    void Entity::setup() {
        this->treeShape->setup();
    }

    Entity::~Entity() {
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


    void Entity::addLinkToSensor(Sensor *sensor) {
        sensors.append(sensor);
        // Connexion de l'input au plug grid !
        for(int i = 0; i < sensor->getInputs().size(); i++) {
            // little cheat
            for(int j = sensor->getInputs()[i]->getConnexions().size(); j < 2; j++) {
                sensor->getInputs()[i]->connectTo(qrand()%brain->getPlugGrid()->getSize(),
                                                  qrand()%brain->getPlugGrid()->getSize(), ((float)qrand())/RAND_MAX*2 -1);
            }
            brain->getPlugGrid()->connectInput(sensor->getInputs()[i]);
        }
    }

    // Modifiers links
    void Entity::addLinkToModifier(Modifier *modifier) {
        modifiers.append(modifier);
        // Connexion de l'output au cerveau
        for(int i = 0; i < modifier->getOutputs().size(); i++) {
            if(modifier->getOutputs()[i]->getConnexionInfo() == "") {
                QString randomFunc = brain->createRandomFunc(5);
                modifier->getOutputs()[i]->setConnexionInfo(QVariant(randomFunc));
            }

            brain->addOut(modifier->getOutputs()[i]);
        }
    }
}
