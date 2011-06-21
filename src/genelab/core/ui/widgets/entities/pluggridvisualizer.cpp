#include "pluggridvisualizer.h"

#include "brain/brainpluggrid.h"
#include "brain/brainin.h"
#include "brain/brainout.h"
#include "brain/synapse.h"
#include "brain/brain.h"

#include <QLayout>
#include <QBoxLayout>
#include <QDebug>
#include <QGLWidget>
#include <QGLContext>


namespace GeneLabCore {
    PlugGridVisualizer::PlugGridVisualizer(QWidget *parent) :
        QWidget(parent)
    {


        this->brain = 0;
        this->view = new QGraphicsView(this);

        this->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
        //this->view->setFixedSize(WIDGET_SIZE, WIDGET_SIZE);
        this->view->setScene(new QGraphicsScene(0, 0, 1000, 1000, this));
        this->layout()->addWidget(this->view);
    }

    int cptP;
    void PlugGridVisualizer::step() {
        cptP++;
        if(cptP%4 == 0)
        this->update();
    }

    void PlugGridVisualizer::paintEvent(QPaintEvent * e) {
        this->view->fitInView(this->view->scene()->sceneRect());

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
        p.setStyle(Qt::NoPen);
        b.setStyle(Qt::SolidPattern);
        float width = 10;
        // On dessine les neurones
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                int bleu  = qMin(255., qMax(0., (-n->activation(n->getNeurons()[i + j * size])) * 255.));
                int rouge = qMin(255., qMax(0., (n->activation(n->getNeurons()[i + j * size])) * 255.));
                int vert  = 0;//qMin(128., qMax(0., (255 - qAbs(n->activation(n->getNeurons()[i + j * size])) * 255.)));
                b.setColor(QColor(rouge, vert, bleu));//  (n->activation(n->getNeurons()[i + j * size]) + 1) * 255/2.0f));
                this->view->scene()->addRect(width * i,
                                             width * j /*+ 70*/, width, width, p, b);
            }
        }


        /*for(int i = 0; i < n->getInputs().size(); i++) {

            // On dessine les entrées
            QPointF startingPoint(SCENE_SIZE/n->getInputs().size() * i + SCENE_SIZE/n->getInputs().size() * 0.5 - 10,
                                  SCENE_SIZE + 100);

            // The input point
            BrainIn* in = n->getInputs().at(i);
            QPen p;
            p.setColor(QColor(0, 255/n->getInputs().size()*i, 255 - 255/n->getInputs().size()*i));
            b.setColor(QColor( p.color().red(), p.color().green(), p.color().blue(), (in->getValue() + 1) * 255/2.0f));

            this->view->scene()->addEllipse(startingPoint.x(), startingPoint.y(), 20, 20, p, b);

            foreach(NeuralConnexion c, in->getConnexions()) {
                p.setWidthF(qAbs(c.weight*5));

                if(c.weight < 0)
                    p.setStyle(Qt::DotLine);
                else
                    p.setStyle(Qt::SolidLine);


                this->view->scene()->addLine(startingPoint.x() + 10, startingPoint.y() + 10,
                                             SCENE_SIZE/size*c.x + SCENE_SIZE/size * 0.5,
                                             SCENE_SIZE/size*c.y + SCENE_SIZE/size * 0.5 + 70, p);
            }
        }*/


        // On dessine les sorties


    }

}
