#include <QtGui/QApplication>
#include "genelabmainwindow.h"

#include "genelabcoreclasses.h"

#include "ogrebulletwindows.h"
#include "creatureviewer/ui/creatureviewerwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GeneLabCore::OgreBulletWindows w;
//    w.show();

    CreatureViewerWindow cw;
    cw.showMaximized();

    return a.exec();
}
