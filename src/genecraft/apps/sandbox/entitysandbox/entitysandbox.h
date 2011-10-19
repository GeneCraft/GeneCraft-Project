#ifndef ENTITYSANDBOX_H
#define ENTITYSANDBOX_H

#include <QMainWindow>

namespace Ui {
    class EntitySandbox;
}

class EntitySandbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit EntitySandbox(QWidget *parent = 0);
    ~EntitySandbox();

private:
    Ui::EntitySandbox *ui;
};

#endif // ENTITYSANDBOX_H
