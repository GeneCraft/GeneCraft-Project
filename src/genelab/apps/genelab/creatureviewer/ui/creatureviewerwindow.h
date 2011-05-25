#ifndef CREATUREVIEWER_H
#define CREATUREVIEWER_H

#include <QMainWindow>
#include "genelabcoreclasses.h"
#include "btBulletDynamicsCommon.h"

namespace Ui {
    class CreatureViewer;
}

using namespace GeneLabCore;

class CreatureViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreatureViewerWindow(QWidget *parent = 0);
    ~CreatureViewerWindow();

public slots:

    void setInspector(QWidget * inspector);
    void setEntity(Entity *entity, btRigidBody *selectedBody);
    void setOpenGLWidget(QWidget * openGLWidget);
    void rigidBodySelected(btRigidBody *rigidBody);

private:

    Ui::CreatureViewer *ui;
    QWidget *inspector;
    QWidget *openGLWidget;
};

#endif // CREATUREVIEWER_H
