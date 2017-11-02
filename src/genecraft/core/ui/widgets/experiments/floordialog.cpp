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

#include "floordialog.h"
#include "ui_floordialog.h"
#include <QJsonObject>

namespace GeneCraftCore {

    FloorDialog::FloorDialog(QJsonObject floorData, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::FloorDialog)
    {
        ui->setupUi(this);
        QString type = floorData["type"].toString();
        if(type == "nofloor") {
            this->ui->cmbType->setCurrentIndex(0);
        } else if (type == "flatland") {
            this->ui->cmbType->setCurrentIndex(1);
        } else if (type == "randomBoxes") {
            this->ui->cmbType->setCurrentIndex(2);
            this->ui->cmbBoxType->setCurrentIndex(0);
            loadBoxes(floorData);
        } else if (type == "stairsUp") {
            this->ui->cmbType->setCurrentIndex(2);
            this->ui->cmbBoxType->setCurrentIndex(1);
            loadBoxes(floorData);
        } else if (type == "stairsDown") {
            this->ui->cmbType->setCurrentIndex(2);
            this->ui->cmbBoxType->setCurrentIndex(2);
            loadBoxes(floorData);
        } else if (type == "slope") {
            this->ui->cmbType->setCurrentIndex(3);
            this->ui->spbSIncl->setValue(floorData["inclinaison"].toDouble());
        }
    }

    void FloorDialog::loadBoxes(QJsonObject map) {
        float width         = map["width"].toDouble();
        float minHeight     = map["minHeight"].toDouble();
        float maxHeight     = map["maxHeight"].toDouble();

        this->ui->spbBWidth->setValue(width);
        this->ui->spbBMinHeight->setValue(minHeight);
        this->ui->spbBMaxHeight->setValue(maxHeight);
    }

    QJsonObject FloorDialog::serialize() {
        QJsonObject data;

        QString type = this->ui->cmbType->currentText();

        if(type == "without") {
            data["type"] = "nofloor";
        } else if(type == "flat") {
            data["type"] = "flatland";
        } else if (type == "boxes") {

            QString boxType = this->ui->cmbBoxType->currentText();

            if(boxType == "random") {
                data["type"] = "randomBoxes";
            } else if(boxType == "stairs (up)") {
                data["type"] = "stairsUp";
            } else if(boxType == "stairs (down)") {
                data["type"] = "stairsDown";
            }

            data["width"]       = this->ui->spbBWidth->value();
            data["minHeight"]   = this->ui->spbBMinHeight->value();
            data["maxHeight"]   = this->ui->spbBMaxHeight->value();

        } else if (type == "slope") {
            data["type"] = "slope";

            data["inclinaison"] = this->ui->spbSIncl->value();
        }


        return data;
    }

    FloorDialog::~FloorDialog()
    {
        delete ui;
    }

    void FloorDialog::on_cmbType_currentIndexChanged(QString type)
    {
        if(type == "without") {
            this->ui->stkParameters->setCurrentWidget(this->ui->pgNo);
        } else if(type == "flat") {
            this->ui->stkParameters->setCurrentWidget(this->ui->pgNo);
        } else if (type == "boxes") {
            this->ui->stkParameters->setCurrentWidget(this->ui->pgBoxes);
        } else if (type == "slope") {
            this->ui->stkParameters->setCurrentWidget(this->ui->pgSlope);
        }
    }

    void FloorDialog::on_cmbBoxType_currentIndexChanged(QString boxType)
    {
        if(boxType == "random") {

        } else if(boxType == "stairs (up)") {

        } else if(boxType == "stairs (down)") {

        }
    }
}
