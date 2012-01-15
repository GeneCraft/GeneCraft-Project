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

#ifndef JSONFILE_H
#define JSONFILE_H

#include "ressource.h"
#include <QVariant>
#include <QFile>

namespace GeneCraftCore {
class JsonFile : public Ressource
{

public:
    explicit JsonFile(QString filename, QObject *parent = 0);
    virtual QVariant load();
    virtual int save(QVariant data);
    virtual int remove();
    virtual QString getLocation();

public:
    QFile f;
    QString filename;

};

}
#endif // JSONFILE_H
