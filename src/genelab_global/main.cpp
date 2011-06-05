#include <QtGui/QApplication>
#include "genelabmainwindow.h"

#include "genelabcoreclasses.h"

#include "widgets/ogrebulletwindows.h"
#include "creatureviewer/ui/creatureviewerwindow.h"

#include "ressources/ressource.h"
#include "ressources/dbrecord.h"
#include "ressources/jsonfile.h"

#include <QDebug>


int main(int argc, char *argv[])
{
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
