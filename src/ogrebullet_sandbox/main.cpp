#include <QtGui/QApplication>
#include "ogrebulletwindows.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "BONJOUR !";
    QApplication a(argc, argv);
    OgreBulletWindows w;
    w.show();

    return a.exec();
}
