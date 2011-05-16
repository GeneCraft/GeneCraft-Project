#include "genelabmainwindow.h"
#include "ui_genelabmainwindow.h"

GeneLabMainWindow::GeneLabMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GeneLabMainWindow)
{
    ui->setupUi(this);
}

GeneLabMainWindow::~GeneLabMainWindow()
{
    delete ui;
}
