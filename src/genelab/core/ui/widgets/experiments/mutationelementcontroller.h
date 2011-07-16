#ifndef MUTATIONELEMENTCONTROLLER_H
#define MUTATIONELEMENTCONTROLLER_H

#include <QWidget>

#include "genelabcoreclasses.h"

namespace Ui {
    class MutationElementController;
}

class MutationElementController : public QWidget
{
    Q_OBJECT

public:
    explicit MutationElementController(GeneLabCore::MutationElement *me, QWidget *parent = 0);
    ~MutationElementController();

public slots:
    void save();
    void weightChanged(int value);

private:
    Ui::MutationElementController *ui;

    GeneLabCore::MutationElement *me;
};

#endif // MUTATIONELEMENTCONTROLLER_H
