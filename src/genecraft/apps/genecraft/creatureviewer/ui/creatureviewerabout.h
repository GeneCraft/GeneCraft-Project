#ifndef CREATUREVIEWERABOUT_H
#define CREATUREVIEWERABOUT_H

#include <QWidget>

namespace Ui {
    class CreatureViewerAbout;
}

class CreatureViewerAbout : public QWidget
{
    Q_OBJECT

public:
    explicit CreatureViewerAbout(QWidget *parent = 0);
    ~CreatureViewerAbout();

private:
    Ui::CreatureViewerAbout *ui;
};

#endif // CREATUREVIEWERABOUT_H
