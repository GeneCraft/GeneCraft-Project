#include "creatureviewerabout.h"
#include "ui_creatureviewerabout.h"

CreatureViewerAbout::CreatureViewerAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreatureViewerAbout)
{
    ui->setupUi(this);
}

CreatureViewerAbout::~CreatureViewerAbout()
{
    delete ui;
}
