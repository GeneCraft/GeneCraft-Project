#ifndef STRUCTURALMUTATIONCONTROLLER_H
#define STRUCTURALMUTATIONCONTROLLER_H

#include <QWidget>
#include "genecraftcoreclasses.h"

#include "mutationelementcontroller.h"

namespace Ui {
    class StructuralMutationController;
}

class StructuralMutationController : public QWidget
{
    Q_OBJECT

public:
    explicit StructuralMutationController(GeneCraftCore::StructuralMutation *mutation,QString name,
                                          GeneCraftCore::StructuralList *list = NULL, QWidget *parent = 0);
    ~StructuralMutationController();

public slots:

    void save();
    void nameToggled(bool checked);
    void addProbabilityChanged(int value);
    void removeProbabilityChanged(int value);
    void replaceProbabilityChanged(int value);

private:
    Ui::StructuralMutationController *ui;

    GeneCraftCore::StructuralMutation *mutation;
    GeneCraftCore::StructuralList *list;
    QList<MutationElementController *> mecs;
};

#endif // STRUCTURALMUTATIONCONTROLLER_H
