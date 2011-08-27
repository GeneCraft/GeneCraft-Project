#include "tools.h"
#include <ctime>
#include <cstdlib>
#include <QDir>
#include <QDebug>

namespace GeneCraftCore {

    Tools::Tools() {
        qsrand((unsigned int)time(NULL));
    }

    int Tools::random(int min, int max) {
        //return (int)((max - min) * qrand()/(btScalar) RAND_MAX + min);
        //return min+int((max-min)*(btScalar)qrand()/(RAND_MAX));
        return min + (qrand() % (int)(max - min + 1));
    }

    btScalar Tools::random(btScalar min, btScalar max) {
        return ((max - min) * ((btScalar) qrand()/RAND_MAX)) + min;
    }
#ifndef BT_USE_DOUBLE_PRECISION
    double Tools::random(double min, double max) {
        return ((max - min) * ((double) qrand()/RAND_MAX)) + min;
    }
#endif

    // Used to clear a QTreeWidget
    void Tools::clearTreeWidget(QTreeWidget * tree)
    {
        for(int i = 0; i < tree->topLevelItemCount(); i++) {
            delete tree->topLevelItem(i);
        }

        tree->clear();
    }

    bool Tools::removeDir(QString dirPath)
    {
        QDir folder(dirPath);
        folder.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
        foreach(QFileInfo fileInfo, folder.entryInfoList())
        {

            if(fileInfo.isDir())
            {
                qDebug() << "- subdir" << fileInfo.filePath();

                if(!removeDir(fileInfo.filePath()))
                    return false;
            }
            else if(fileInfo.isFile())
            {
                qDebug() << "- subfile" << fileInfo.filePath();

                if(!QFile::remove(fileInfo.filePath()))
                {
                    qDebug() << "Unable to remove file : " << fileInfo.filePath();
                    return false;
                }
            }
        }

        if(!folder.rmdir(dirPath))
        {
            qDebug() << "Unable to remove folder : " << dirPath << ". Maybe this folder is not empty";
            return false;
        }

        return true;
    }

}
