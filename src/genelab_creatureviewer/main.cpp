#include <QtGui/QApplication>
#include "ui/ogrebulletwindows.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GeneLabCore::OgreBulletWindows w;
    w.show();

    return a.exec();
}
