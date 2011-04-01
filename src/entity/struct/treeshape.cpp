#include "treeshape.h"
#include "struct/fixation.h"
#include <QDebug>
#include <QStringBuilder>

namespace GeneLabOgreBullet {
    TreeShape::TreeShape(QObject *parent) :
        QObject(parent)
    {
        this->root = NULL;
    }

    TreeShape::~TreeShape() {
        delete root;
    }

    void TreeShape::setRoot(Fixation *root) {
        this->root = root;
    }

    Fixation* TreeShape::getRoot() {
        return this->root;
    }

    void TreeShape::print() {
        qDebug() << "Tree shape : ";
        if(root == NULL)
            qDebug() << " empty ";
        else {
            qDebug() << root->toString();
        }
    }
}
