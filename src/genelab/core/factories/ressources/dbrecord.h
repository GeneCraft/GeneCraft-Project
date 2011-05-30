#ifndef DBRECORD_H
#define DBRECORD_H

#include "ressource.h"
#include <QNetworkReply>

namespace GeneLabCore {

    struct DataBase {
        QString url;
        int port;
        QString dbName;
    };

    enum RequestType {GET, POST, PUT, DELETE};

    class DbRecord : public Ressource
    {
        Q_OBJECT
    public:
        explicit DbRecord(DataBase db, QString id, QObject *parent = 0);

        virtual QVariant load();
        virtual void save(QVariant data);

    signals:

    public slots:

    protected slots:
        void networkReply(QNetworkReply*);
        void request(QString url, RequestType verb, QString data = "");

    protected:
        DataBase db;
        QString id;
        QString rev;
        QNetworkReply* r;

    };

}
#endif // DBRECORD_H
