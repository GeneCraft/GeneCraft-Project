#ifndef GENELABMAINWINDOW_H
#define GENELABMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class GeneLabMainWindow;
}

class GeneLabMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GeneLabMainWindow(QWidget *parent = 0);
    ~GeneLabMainWindow();

private:
    Ui::GeneLabMainWindow *ui;
};

#endif // GENELABMAINWINDOW_H
