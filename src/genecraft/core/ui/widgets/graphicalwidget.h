#ifndef GRAPHICALWIDGET_H
#define GRAPHICALWIDGET_H

#include <QWidget>

namespace GeneCraftCore {
class GraphicalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicalWidget(QWidget *parent = 0);

        virtual void step() = 0;
signals:

public slots:

};
}
#endif // GRAPHICALWIDGET_H
