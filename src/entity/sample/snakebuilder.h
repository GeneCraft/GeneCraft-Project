#ifndef SNAKEBUILDER_H
#define SNAKEBUILDER_H

#include "entitybuilder.h"

class SnakeBuilder : public EntityBuilder
{
    Q_OBJECT
public:
    explicit SnakeBuilder(int length, float pieceLength, QObject *parent = 0);

    Entity* build();

signals:

public slots:

private:
    int length;
    float pieceLength;

};

#endif // SNAKEBUILDER_H
