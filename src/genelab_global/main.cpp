#include <QtGui/QApplication>
#include "genelabmainwindow.h"

#include "genelabcoreclasses.h"

#include "widgets/ogrebulletwindows.h"
#include "creatureviewer/ui/creatureviewerwindow.h"

#include "ressources/ressource.h"
#include "ressources/dbrecord.h"
#include "ressources/jsonfile.h"

#include <QDebug>
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    // ----------------------------------------------------------------------------
    // This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle

    // ----------------------------------------------------------------------------

#ifdef __APPLE__
 CFBundleRef mainBundle = CFBundleGetMainBundle();
 CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
 char path[PATH_MAX];
 if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
 {
     // error!
 }
 CFRelease(resourcesURL);

 QString directoryPath = path;
 directoryPath += "/Contents/MacOS/";
 chdir(directoryPath.toStdString().c_str());
 //system((QString("cd ") + directoryPath).toStdString().c_str());
 char newPath[500];
 getcwd(newPath, 500);
 qDebug() << "Current Path: " << directoryPath << newPath;
#endif
    QApplication a(argc, argv);
    //GeneLabCore::OgreBulletWindows w;
//    w.show();
/*
    // That's how to use ressources !!
    // Either from couchDb database
    // Or JsonFile

    DataBase db;
    db.dbName = "genelab";
    db.url = "http://www.ai-battle.org";
    db.port = 80;

    Ressource* r = new DbRecord(db, "test");

    QVariantMap v = r->load().toMap();
    v.insert("Bonjour", "Couchdb !");
    r->save(v);
    v.insert("Bonjour2", "Couchdb !");
    r->save(v);
    v = r->load().toMap();

    Ressource* rr = new JsonFile("MyTest");
    rr->save(v);
    qDebug() << rr->load();
     qDebug() << v;
*/

    CreatureViewerWindow cw;
    cw.showMaximized();

    return a.exec();
}
