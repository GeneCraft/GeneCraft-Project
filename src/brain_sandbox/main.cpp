#include <QtGui/QApplication>
#include "brainapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BrainApp w;
    w.show();

    return a.exec();
}
