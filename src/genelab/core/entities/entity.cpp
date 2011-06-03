#include "entity.h"
#include <QDebug>
#include "fixation.h"
#include "treeshape.h"
#include "brainfunctional.h"
#include "brainin.h"

#include "brainpluggrid.h"
#include "brainout.h"
#include "sensor.h"
#include "modifier.h"

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
            for(int j = 0; j < 1; j++) {
                //qDebug() << "ajout d'une connexion de l'input !";
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
            QString randomFunc = brain->createRandomFunc(5);
            //qDebug() << randomFunc;
            modifier->getOutputs()[i]->setConnexionInfo(QVariant(randomFunc));
            brain->addOut(modifier->getOutputs()[i]);
        }
    }
}
