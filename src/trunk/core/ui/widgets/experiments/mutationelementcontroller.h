#ifndef MUTATIONELEMENTCONTROLLER_H
#define MUTATIONELEMENTCONTROLLER_H

#include <QWidget>

#include "genecraftcoreclasses.h"

namespace Ui {
    class MutationElementController;
}

class MutationElementController : public QWidget
{
    Q_OBJECT

public:
    explicit MutationElementController(GeneCraftCore::MutationElement *me, QWidget *parent = 0);
    ~MutationElementController();

public slots:
    void save();
    void weightChanged(int value);

private:
    Ui::MutationElementController *ui;

    GeneCraftCore::MutationElement *me;
};

#endif // MUTATIONELEMENTCONTROLLER_H
