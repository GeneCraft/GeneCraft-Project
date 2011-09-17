#include "floordialog.h"
#include "ui_floordialog.h"

namespace GeneCraftCore {

    FloorDialog::FloorDialog(QVariant floorData, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::FloorDialog)
    {
        ui->setupUi(this);
        QString type = floorData.toMap()["type"].toString();
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
            this->ui->spbSIncl->setValue(floorData.toMap()["inclinaison"].toFloat());
        }
    }

    void FloorDialog::loadBoxes(QVariant data) {
        QVariantMap map = data.toMap();
        float width         = map["width"].toFloat();
        float minHeight     = map["minHeight"].toFloat();
        float maxHeight     = map["maxHeight"].toFloat();

        this->ui->spbBWidth->setValue(width);
        this->ui->spbBMinHeight->setValue(minHeight);
        this->ui->spbBMaxHeight->setValue(maxHeight);
    }

    QVariant FloorDialog::serialize() {
        QVariantMap data;

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
