#ifndef EXPERIMENTSPROPERTIESCONTROLLER_H
#define EXPERIMENTSPROPERTIESCONTROLLER_H

#include <QWidget>

namespace Ui {
    class ExperimentsPropertiesController;
}

class ExperimentsPropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit ExperimentsPropertiesController(QWidget *parent = 0);
    ~ExperimentsPropertiesController();
public slots:
    void save();
private:
    Ui::ExperimentsPropertiesController *ui;
};

#endif // EXPERIMENTSPROPERTIESCONTROLLER_H
