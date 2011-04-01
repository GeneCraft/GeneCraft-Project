#include "snakefamily.h"
#include "struct/treeshape.h"
#include "struct/fixation.h"
#include "struct/bone.h"
#include "ogrebulletentity.h"
#include <QVariant>
#include <cmath>


namespace GeneLabOgreBullet {
    SnakeFamily::SnakeFamily(QVariant data, QObject *parent) :
        OgreBulletEntityFamily(parent)
    {
        this->length = data.toMap()["length"].toInt();
        this->pieceLength = data.toMap()["piecelength"].toFloat();
    }

    OgreBulletEntity* SnakeFamily::build() {
        OgreBulletEntity* snake = new OgreBulletEntity("Snaky"+QString::number(length), "Snake", 1);
        TreeShape* snakeShape = new TreeShape();
        Fixation* root = new Fixation();
        snakeShape->setRoot(root);
        snake->setShape(snakeShape);

        for(int i = 0; i < length; i++) {
            Bone* b = root->addBone(0., M_PI/2., M_PI + M_PI/2., 0, M_PI,
               pieceLength/(1+1.6180339887 * (i) / 10));

            root = b->getFixation();
        }

        return snake;

    }

    QVariant SnakeFamily::serialize() {
        QVariantMap data;
        data["length"] = QVariant(length);
        data["piecelength"] = QVariant(pieceLength);
        return data;
    }
}
