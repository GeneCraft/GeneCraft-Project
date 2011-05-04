#include <QtGui/QApplication>
#include "ogrebulletwindows.h"
#include "factory/jsonloader.h"
#include <QDebug>

int main(int argc, char *argv[])
{
//    qDebug() << "BONJOUR !";
//    GeneLabCore::JsonLoader* loader = new GeneLabCore::JsonLoader();
//    QVariant data = loader->loadFrom("file", "test.json");
//    qDebug() << data.toMap()["a"].toString();

    QApplication a(argc, argv);
    OgreBulletWindows w;
    w.showMaximized();

    return a.exec();
}
