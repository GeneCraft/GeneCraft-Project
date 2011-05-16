#ifndef BRAINAPP_H
#define BRAINAPP_H

#include <QMainWindow>
#include <QTimer>
#include "genelabcoreclasses.h"

using namespace GeneLabCore;

namespace Ui {
    class BrainApp;
}

class BrainApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrainApp(QWidget *parent = 0);
    ~BrainApp();

private slots:
    void tick();
private:
    Ui::BrainApp *ui;
    QTimer* timer;
    BrainEngine* engine;
};

#endif // BRAINAPP_H
