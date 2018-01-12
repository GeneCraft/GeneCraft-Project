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

#include "brain.h"
#include "brainpluggrid.h"
#include "tools.h"
#include "qmath.h"
#include <QDebug>

namespace GeneCraftCore {
    Brain::Brain(QObject *parent) :
        QObject(parent)
    {
        // BRAIN MODIF TRY
        this->plugGrid = new BrainPlugGrid();
        this->frequency = qrand()%60 + 1;
    }

    Brain::Brain(QJsonObject data) {
        this->plugGrid = new BrainPlugGrid();
        this->frequency = data["frequency"].toInt();
        if(frequency <= 0) {
            frequency = 1;
        }
        if(frequency > 60) {
            frequency = 60; // 10 per sec
        }
    }

    QJsonObject Brain::serialize() {
        QJsonObject data;
        data.insert("frequency", this->frequency);
        return data;
    }

    /*int Brain::randomPlugGridSize()
    {
        return pow(2,Tools::random(1,6));
    }*/
}
