#include <QtGui/QApplication>
#include "entitysandbox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EntitySandbox w;
    w.show();

    return a.exec();
}
