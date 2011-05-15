#include "neuralnetworkvisualizer.h"

#include "entity/neural/neuralnetwork.h"
#include "entity/neural/neuralin.h"
#include "entity/neural/neuralout.h"
#include "entity/neural/synapse.h"

#include "engine/brainengine.h"

#include <QLayout>
#include <QBoxLayout>
#include <QDebug>

#define SCENE_SIZE 51*10

namespace GeneLabWidget {
    using namespace GeneLabCore;
    NeuralNetworkVisualizer::NeuralNetworkVisualizer(BrainEngine* networks, QWidget *parent) :
        QWidget(parent)
    {
        this->networks = networks;
        this->view = new QGraphicsView(this);
        this->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
        this->view->setFixedSize(300, 300 + 140);
        this->view->setScene(new QGraphicsScene(0, 0, SCENE_SIZE, SCENE_SIZE + 140, this));

        this->layout()->addWidget(this->view);
    }

    int cpt = 0;
    void NeuralNetworkVisualizer::step() {
        cpt++;
        if(!(cpt % 10))
        this->update();
    }

    void NeuralNetworkVisualizer::paintEvent(QPaintEvent * e) {

        this->view->scene()->clear();
        this->view->fitInView(0, 0, SCENE_SIZE, SCENE_SIZE + 140);

        if(networks->getNetworks().size() == 0) {
            this->view->scene()->addText("No network");
            return;
        }

        // On r�cup�re le bon r�seau de neurone
        NeuralNetwork* n = this->networks->getNetworks()[0];
        int size = n->getSize();

        QBrush b;
        QPen p;
        p.setStyle(Qt::NoPen);
        b.setStyle(Qt::SolidPattern);
        float width = SCENE_SIZE/size;
        // On dessine les neurones
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                b.setColor(QColor( 0,0,0,  (n->activation(n->getNeurons()[i + j * size]) + 1) * 255/2.0f));
                this->view->scene()->addRect(width * i,
                                             width * j + 70, width, width, p, b);
                //this->view->scene()->addEllipse();
            }
        }
/*

        for(int i = 0; i < n->getInputs().size(); i++) {

            // On dessine les entr�es
            QPointF startingPoint(SCENE_SIZE/n->getInputs().size() * i + SCENE_SIZE/n->getInputs().size() * 0.5 - 10,
                                  SCENE_SIZE + 100);

            // The input point
            NeuralIn* in = n->getInputs().at(i);
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
        }

*/
        /*
        for(int i = 0; i < n->getOutputs().size(); i++) {

            // On dessine les entr�es
            QPointF startingPoint(SCENE_SIZE/n->getOutputs().size() * i + SCENE_SIZE/n->getOutputs().size() * 0.5 - 10,
                                  10);

            // The input point
            NeuralOut* out = n->getOutputs().at(i);
            QPen p;
            p.setColor(QColor(255, 255/n->getOutputs().size()*i, 0));
            b.setColor(QColor( p.color().red(), p.color().green(), p.color().blue(), (out->getValue() + 1) * 255/2));

            this->view->scene()->addEllipse(startingPoint.x(), startingPoint.y(), 20, 20, p, b);

            foreach(NeuralConnexion c, out->getConnexions()) {
                p.setWidthF(qAbs(c.weight*5));

                if(c.weight < 0)
                    p.setStyle(Qt::DotLine);
                else
                    p.setStyle(Qt::SolidLine);

                this->view->scene()->addLine(startingPoint.x() + 10, startingPoint.y() + 10,
                                             SCENE_SIZE/size*c.x + SCENE_SIZE/size * 0.5,
                                             SCENE_SIZE/size*c.y + SCENE_SIZE/size * 0.5 + 70, p);
            }
        }
*/
        // On dessine les sorties


    }

}
