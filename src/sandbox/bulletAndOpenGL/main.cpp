#include <QtGui/QApplication>
#include <iostream>
#include "Views/OpenGL/GLWidget_1.h"
#include "Views/MainWindow.h"
#include "Views/OpenGL/GLCreatureViewer.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *mw = new MainWindow();
    mw->show();

    //GLCreatureViewer *cw = new GLCreatureViewer();
    //cw->show();

    // Very simple mode
    //GLWidget_1 *w = new GLWidget_1();
    //w->show();

    return a.exec();
}
