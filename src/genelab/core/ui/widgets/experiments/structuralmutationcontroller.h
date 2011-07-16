#ifndef STRUCTURALMUTATIONCONTROLLER_H
#define STRUCTURALMUTATIONCONTROLLER_H

#include <QWidget>
#include "genelabcoreclasses.h"

#include "mutationelementcontroller.h"

namespace Ui {
    class StructuralMutationController;
}

class StructuralMutationController : public QWidget
{
    Q_OBJECT

public:
    explicit StructuralMutationController(GeneLabCore::StructuralMutation *mutation,QString name,
                                          GeneLabCore::StructuralList *list = NULL, QWidget *parent = 0);
    ~StructuralMutationController();

public slots:

    void save();
    void nameToggled(bool checked);
    void addProbabilityChanged(int value);
    void removeProbabilityChanged(int value);
    void replaceProbabilityChanged(int value);

private:
    Ui::StructuralMutationController *ui;

    GeneLabCore::StructuralMutation *mutation;
    GeneLabCore::StructuralList *list;
    QList<MutationElementController *> mecs;
};

#endif // STRUCTURALMUTATIONCONTROLLER_H
