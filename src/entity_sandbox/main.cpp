#include <QtGui/QApplication>
#include "entitysandbox.h"
#include "sample/snakebuilder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EntitySandbox w;
    w.show();

    SnakeBuilder snakeBuilder(10, 100.);
    Entity* snake = snakeBuilder.build();

    snake->print();

    return a.exec();
}
