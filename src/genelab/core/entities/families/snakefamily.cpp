#include "snakefamily.h"
#include "body/treeshape.h"
#include "body/fixation.h"
#include "body/bone.h"
#include <QVariant>
#include <cmath>
#include "tools.h"
#include "sensors/accelerometersensor.h"
#include "sensors/positionsensor.h"
#include "sensors/gyroscopicsensor.h"

namespace GeneLabCore {

    SnakeFamily::SnakeFamily(QObject *parent) :
        EntityFamily(parent)
    {
        this->length = Tools::random(5,15);
        this->pieceLength = Tools::random(1,10);
        this->pieceRadius = Tools::random(0.2,2.0);
    }

    SnakeFamily::SnakeFamily(QVariant data, QObject *parent) :
        EntityFamily(parent)
    {
        this->length = data.toMap()["length"].toInt();

        this->pieceLength = data.toMap()["piecelength"].toFloat();
        this->pieceRadius = data.toMap()["pieceRadius"].toFloat();
    }

    Entity* SnakeFamily::createEntity(btShapesFactory* factory, const btVector3 &position) {

        Entity* snake = new Entity("Snaky"+QString::number(length), "Snake", 1);
        snake->setBrain(new BrainFunctional(Brain::randomPlugGridSize()));

        TreeShape* snakeShape = new TreeShape(factory);

        btTransform initTransform;
        initTransform.setIdentity();
        initTransform.setOrigin(position);

        Fixation* root = new Fixation(factory,pieceRadius,initTransform);
        snakeShape->setRoot(root);
        snake->setShape(snakeShape);

        float angle = M_PI - M_PI / 3;

        // Build body
        for(int i = 0; i < length; i++) {
            Bone* b = root->addBone(0., 0.,
                                    pieceRadius/(1+1.6180339887 * (i) / 10),
                                    pieceLength/(1+1.6180339887 * (i) / 10),
                                    pieceRadius/(1+1.6180339887 * (i) / 10),
                                    btVector3(-angle,-M_PI/4,-angle),
                                    btVector3(angle,M_PI/4,angle));

            b->getEndFixation()->addSensor(new GyroscopicSensor(b->getEndFixation()));
            b->getEndFixation()->addSensor(new PositionSensor(snakeShape->getRoot(),b->getEndFixation()));

            root = b->getEndFixation();
        }

        return snake;
    }

    QVariant SnakeFamily::serialize() {
        QVariantMap data;
        data["length"] = QVariant(length);
        data["piecelength"] = QVariant(pieceLength);
        data["pieceRadius"] = QVariant(pieceRadius);
        return data;
    }
}
