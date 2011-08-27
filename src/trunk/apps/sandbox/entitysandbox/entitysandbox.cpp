#include "entitysandbox.h"
#include "ui_entitysandbox.h"

EntitySandbox::EntitySandbox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EntitySandbox)
{
    ui->setupUi(this);
}

EntitySandbox::~EntitySandbox()
{
    delete ui;
}
