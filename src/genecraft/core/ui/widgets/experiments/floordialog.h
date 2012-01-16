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

#ifndef FLOORDIALOG_H
#define FLOORDIALOG_H

#include <QDialog>
#include <QVariant>

namespace Ui {
    class FloorDialog;
}

namespace GeneCraftCore {

    class FloorDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit FloorDialog(QVariant floorData, QWidget *parent = 0);
        QVariant serialize();
        ~FloorDialog();


    private:
        Ui::FloorDialog *ui;
        void loadBoxes(QVariant data);

    private slots:
        void on_cmbBoxType_currentIndexChanged(QString );
        void on_cmbType_currentIndexChanged(QString );
    };

}

#endif // FLOORDIALOG_H
