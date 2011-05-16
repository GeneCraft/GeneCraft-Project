#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QObject>
#include <QVariant>

namespace GeneLabCore {

    class JsonLoader : public QObject
    {
        Q_OBJECT
    public:
        explicit JsonLoader(QObject *parent = 0);

        QVariant loadFrom(QString ressourceType, QString id);
        void     saveTo(QString ressourceType, QString id, QVariant data);

    signals:

    public slots:


    };
}

#endif // JSONLOADER_H
