#include "pluggriddesignvisualizer.h"

#include "brain.h"
#include "brainpluggrid.h"
#include "brainin.h"
#include "synapse.h"
#include "sensor.h"
#include "modifier.h"
#include <QLayout>
#include <QBoxLayout>

namespace GeneLabCore {
PlugGridDesignVisualizer::PlugGridDesignVisualizer(QWidget *parent) :
    QWidget(parent)
{
    this->brain = 0;
    this->view = new QGraphicsView(this);
    this->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
    //this->view->setFixedSize(WIDGET_SIZE, WIDGET_SIZE);
    this->view->setScene(new QGraphicsScene(0, 0, 1000, 1000, this));

    this->layout()->addWidget(this->view);
}

void PlugGridDesignVisualizer::paintEvent(QPaintEvent * e) {

    if(this->brain == 0)
        return;

    this->view->scene()->clear();
    this->view->scene()->setSceneRect(0, 0,brain->getPlugGrid()->getSize()*10, brain->getPlugGrid()->getSize()*10);
    this->view->fitInView(0, 0, brain->getPlugGrid()->getSize()*10, brain->getPlugGrid()->getSize()*10);


    // On récupère le bon réseau de neurone
    BrainPlugGrid* n = brain->getPlugGrid();
    int size = n->getSize();

    QBrush b;
    QPen p;
    //p.setStyle(Qt::NoPen);
    b.setStyle(Qt::SolidPattern);
    float width = 10;
    // On dessine les neurones
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            int bleu  = 1;//qMin(255., qMax(0., (-n->activation(n->getNeurons()[i + j * size])) * 255.));
            int rouge = 0;//qMin(255., qMax(0., (n->activation(n->getNeurons()[i + j * size])) * 255.));
            int vert  = 0;//qMin(255., qMax(0., (255 - qAbs(n->activation(n->getNeurons()[i + j * size])) * 255.)));
            b.setColor(QColor(rouge, vert, bleu));//  (n->activation(n->getNeurons()[i + j * size]) + 1) * 255/2.0f));
            this->view->scene()->addRect(width * i,
                                         width * j /*+ 70*/, width, width, p, b);
        }
    }


    for(int i = 0; i < n->getInputs().size(); i++) {

        // On dessine les entrées
//        QPointF startingPoint(brain->getPlugGrid()->getSize()*10/n->getInputs().size() * i + brain->getPlugGrid()->getSize()*10/n->getInputs().size() * 0.5 - 10,
 //                             brain->getPlugGrid()->getSize()*10 + 100);

        // The input point
        BrainIn* in = n->getInputs().at(i);
        QPen p;

        foreach(NeuralConnexion c, in->getConnexions()) {
            int bleu  = qMin(255., qMax(0., -c.weight * 255.));
            int rouge = qMin(255., qMax(0., c.weight * 255.));
            int vert  = qMin(255., qMax(0., (255 - qAbs(c.weight) * 255.)));
            p.setColor(QColor(rouge, vert, bleu));
            b.setColor(QColor(rouge, vert, bleu));

            p.setWidthF(qAbs(c.weight));

            if(c.weight < 0)
                p.setStyle(Qt::DotLine);
            else
                p.setStyle(Qt::SolidLine);


            this->view->scene()->addEllipse(10*c.x+5, 10*c.y+5, 10, 10, p, b);

            /*this->view->scene()->addLine(startingPoint.x() + 10, startingPoint.y() + 10,
                                         brain->getPlugGrid()->getSize()*10/size*c.x + brain->getPlugGrid()->getSize()*10/size * 0.5,
                                         brain->getPlugGrid()->getSize()*10/size*c.y + brain->getPlugGrid()->getSize()*10/size * 0.5 + 70, p);
            */
            }
    }

    foreach(Sensor* selectedSensor, selectedSensors) {
        for(int i = 0; i < selectedSensor->getInputs().size(); i++) {
            // The input point
            BrainIn* in = selectedSensor->getInputs().at(i);
            QPen p;

            foreach(NeuralConnexion c, in->getConnexions()) {
                int bleu  = 255;//qMin(255., qMax(0., -c.weight * 255.));
                int rouge = 255;//qMin(255., qMax(0., c.weight * 255.));
                int vert  = 255;//qMin(255., qMax(0., (255 - qAbs(c.weight) * 255.)));

                p.setColor(QColor(rouge, vert, bleu));
                bleu  = qMin(255., qMax(0., -c.weight * 255.));
                rouge = qMin(255., qMax(0., c.weight * 255.));
                vert  = qMin(255., qMax(0., (255 - qAbs(c.weight) * 255.)));
                b.setColor(QColor(rouge, vert, bleu));

                p.setWidthF(2);


                this->view->scene()->addEllipse(10*c.x+5, 10*c.y+5, 10, 10, p, b);

                /*this->view->scene()->addLine(startingPoint.x() + 10, startingPoint.y() + 10,
                                             brain->getPlugGrid()->getSize()*10/size*c.x + brain->getPlugGrid()->getSize()*10/size * 0.5,
                                             brain->getPlugGrid()->getSize()*10/size*c.y + brain->getPlugGrid()->getSize()*10/size * 0.5 + 70, p);
                */
                }
        }
    }
}
}
