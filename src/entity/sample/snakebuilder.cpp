#include "snakebuilder.h"
#include "struct/treeshape.h"
#include <cmath>

SnakeBuilder::SnakeBuilder(int length, float pieceLength, QObject *parent) :
    EntityBuilder(parent)
{
    this->length = length;
    this->pieceLength = pieceLength;
}

Entity* SnakeBuilder::build() {
    Entity* snake = new Entity("Snaky"+QString::number(length), "Snake", 1);
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
