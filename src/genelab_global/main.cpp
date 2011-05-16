#include <QtGui/QApplication>
#include "genelabmainwindow.h"

#include "genelabcoreclasses.h"

#include "ui/widgets/ogrebulletwindows.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GeneLabCore::OgreBulletWindows w;
    w.show();

    return a.exec();
}
