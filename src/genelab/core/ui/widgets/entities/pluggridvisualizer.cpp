#include "pluggridvisualizer.h"

#include "brain/brainpluggrid.h"
#include "brain/brainin.h"
#include "brain/brainout.h"
#include "brain/synapse.h"
#include "brain/brain.h"

#include <QLayout>
#include <QBoxLayout>
#include <QDebug>

namespace GeneLabCore {
    PlugGridVisualizer::PlugGridVisualizer(QWidget *parent) :
        QWidget(parent)
    {


        this->brain = 0;
        this->view = new QGraphicsView(this);

        this->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
        //this->view->setFixedSize(WIDGET_SIZE, WIDGET_SIZE);
        this->view->setScene(new QGraphicsScene(0, 0, 1, 1, this));
        this->layout()->addWidget(this->view);
    }

    int cptP;
    void PlugGridVisualizer::step() {
        cptP++;
        if(cptP%10 == 0)
            this->update();
    }

    void PlugGridVisualizer::paintEvent(QPaintEvent *) {
        this->view->fitInView(this->view->scene()->sceneRect(), Qt::KeepAspectRatio);

        if(this->brain == 0)
            return;

        this->view->scene()->clear();
        this->view->scene()->setSceneRect(0, 0,1, 1);
        this->view->fitInView(0, 0, 1, 1, Qt::KeepAspectRatio);


        // On rcupre le bon rseau de neurone
        BrainPlugGrid* n = brain->getPlugGrid();
        //int size = n->getSize();

        QBrush b;
        QPen p;
        p.setStyle(Qt::SolidLine);
        b.setStyle(Qt::SolidPattern);
        foreach(BrainIn* in, n->getInputs()) {
            foreach(NeuralConnexion c, in->getConnexions()) {
                int bleu  = qMin(255., qMax(0., (-(in->getValue()*c.weight)) * 255.));
                int rouge = qMin(255., qMax(0., ((in->getValue()*c.weight)) * 255.));
                int vert  = 0;//qMin(128., qMax(0., (255 - qAbs(n->activation(n->getValue(i,j))) * 255.)));                b.setColor(QColor(rouge, vert, bleu));//  (n->activation(n->getValue(i,j)) + 1) * 255/2.0f));
                b.setColor(QColor(rouge, vert, bleu, 50));//  (n->activation(n->getValue(i,j)) + 1) * 255/2.0f));

                this->view->scene()->addEllipse(c.x - c.distance, c.y - c.distance, c.distance*2., c.distance*2., p, b);
            }
        }

        // On dessine les neurones
        /*for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                int bleu  = qMin(255., qMax(0., (-n->activation(n->getValue(i/(btScalar)size,j/(btScalar)size))) * 255.));
                int rouge = qMin(255., qMax(0., (n->activation(n->getValue(i/(btScalar)size,j/(btScalar)size))) * 255.));
                int vert  = 0;//qMin(128., qMax(0., (255 - qAbs(n->activation(n->getValue(i,j))) * 255.)));
                b.setColor(QColor(rouge, vert, bleu));//  (n->activation(n->getValue(i,j)) + 1) * 255/2.0f));
                this->view->scene()->addRect(width * i,
                                             width * j, width, width, p, b);
            }
        }*/


        /*for(int i = 0; i < n->getInputs().size(); i++) {

            // On dessine les entres
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
