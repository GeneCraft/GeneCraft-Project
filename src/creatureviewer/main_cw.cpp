/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>

#include "genecraftcoreclasses.h"

#include "widgets/ogrebulletwindows.h"
#include "creatureviewer/ui/creatureviewerwindow.h"

#include "ressources/ressource.h"
#include "ressources/dbrecord.h"
#include "ressources/jsonfile.h"
#include "ressources/ressourcesmanager.h"

#include <QDebug>
#include <QSplashScreen>
#include <QSettings>

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <iostream>
using namespace std;

QApplication *a;

#define RESSOURCES_FOLDER_SETTING_KEY "RESSOURCES_FOLDER"
#define NB_LAUNCHES_SETTING_KEY "NB_LAUNCHES"

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

    // create application
    a = new QApplication(argc, argv);

    // shpow splash
    QPixmap pixmap(":img/logos/splash");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Loading...");

    // loading...
    CreatureViewerWindow cw;
    a->processEvents(); // This is used to accept a click on the screen so that user can cancel the screen
    loadStyleSheet("styleSheet");

    // shows
    cw.showMaximized();
    splash.finish(&cw);

    // DOESN'T WORK ?!?
    // First launch
    QSettings mySettings;
    //mySettings.remove(NB_LAUNCHES_SETTING_KEY);
    if(!mySettings.contains(NB_LAUNCHES_SETTING_KEY)) {
        mySettings.setValue(NB_LAUNCHES_SETTING_KEY, 1);
        mySettings.setValue(RESSOURCES_FOLDER_SETTING_KEY, "ressources");
    }
    else {
        mySettings.setValue(NB_LAUNCHES_SETTING_KEY, mySettings.value(NB_LAUNCHES_SETTING_KEY).toInt() + 1);
    }
    qDebug() << "#launch : " <<  mySettings.value(NB_LAUNCHES_SETTING_KEY).toInt();
    qDebug() << "ressources folder : " <<  mySettings.value(RESSOURCES_FOLDER_SETTING_KEY).toString();


    return a->exec();
}
