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

#include "jsonfile.h"

#include <QTextStream>
#include <QDebug>

#include "qxtjson.h"
#include <QtScript>

namespace GeneCraftCore {
    JsonFile::JsonFile(QString filename, QObject *parent) :
        Ressource(parent), f(filename), filename(filename)
    {

    }


    int JsonFile::save(QVariant data) {
        f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        QTextStream out(&f);

        QString beautifull = Ressource::beautifullJson(data);
        out << beautifull;

        f.close();

        return f.error();
    }

    QVariant JsonFile::load() {
        QString content;
        if(f.exists()) {
            // On ouvre le fichier et on le lit !
            if(f.open(QIODevice::ReadOnly | QIODevice::Text))
                content = f.readAll();
        } else {
            qDebug() << "Could not open " << f.fileName();
        }

        f.close();
        return QxtJSON::parse(content);
    }

    int JsonFile::remove() {
        if(f.exists()) {
            return f.remove();
        }
        return false;
    }

    QString JsonFile::getLocation() {
        return "local";
    }
}
