#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <QObject>
#include <QVariant>


namespace GeneLabCore {

    class JsonFile;
    class DbRecord;

    class Ressource : public QObject
    {

    public:
        explicit Ressource(QObject *parent = 0);
        ~Ressource();

        /**
          * Load data from ressource
          */
        virtual QVariant load() = 0;

        /**
          * Save data to ressource
          *
          * @return 0 if ok, else error code.
          */
        virtual int save(QVariant data) = 0;

        /**
          * Remove ressource
          */
        virtual int remove() = 0;

        /**
          * Create a ressource from a ressource metadata
          */
        static Ressource* unserialize(QVariant v);

        /**
          * Create an include QVariant bloc,
          * which can be loaded by the static Ressource::load function
          */
        static QVariant serialize(JsonFile *r);
        static QVariant serialize(DbRecord *r);

        /**
          * Load data from either a ressource data, or the real data
          */
        static QVariant load(QVariant data);

        static QString beautifullJson(QVariant data);
        static QString beautifullJson(QString data);

    };

}
#endif // RESSOURCE_H
