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

#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <QObject>
#include <QVariant>


namespace GeneCraftCore {

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
          * To get the location
          */
        virtual QString getLocation() = 0;

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
