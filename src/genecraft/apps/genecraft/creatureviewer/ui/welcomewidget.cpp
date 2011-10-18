#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    connect(ui->pbBackToWelcomePage,SIGNAL(clicked()),this,SLOT(backToWelcomePage()));
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::backToWelcomePage() {

    ui->webView->setUrl(QUrl("qrc:/help/welcome.html"));
}
