#include <QtGui/QApplication>
#include "genelabmainwindow.h"

#include "genelabcoreclasses.h"

#include "widgets/ogrebulletwindows.h"
#include "creatureviewer/ui/creatureviewerwindow.h"

#include "ressources/ressource.h"
#include "ressources/dbrecord.h"
#include "ressources/jsonfile.h"
#include "ressources/ressourcesmanager.h"

#include <QDebug>

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <iostream>
using namespace std;

QApplication *a;

void loadStyleSheet(const QString &sheetName)
{
    QFile file(/*":/qss/" + */sheetName + ".qss");

    if(file.exists()){
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        a->setStyleSheet(styleSheet);
    }
}

int main(int argc, char *argv[])
{
    // ----------------------------------------------------------------------------
    // This makes relative paths work in C++
    // by changing directory to the binary folder inside the .app bundle
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

    DataBase database;
    database.dbName = "/db/genecraft/";
    database.url = "http://www.genecraft-project.org";
    database.port = 80;

    RessourcesManager* ressourceManager = new RessourcesManager(database, QDir("ressources"));
    ressourceManager->reloadDir();

    qDebug() << "WORLDS" << ressourceManager->getWorlds().size();
    qDebug() << "CREATURES" << ressourceManager->getCreatures().size();
    qDebug() << "EXPERIMENTS" << ressourceManager->getExperiments().size();

    a = new QApplication(argc, argv);

    CreatureViewerWindow cw;
    cw.showMaximized();

    loadStyleSheet("styleSheet");

    return a->exec();
}


