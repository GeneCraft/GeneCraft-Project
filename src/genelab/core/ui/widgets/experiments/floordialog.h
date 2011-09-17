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
