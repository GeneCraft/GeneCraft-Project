#include "treeshape.h"
#include <QDebug>
#include <QStringBuilder>

TreeShape::TreeShape(QObject *parent) :
    Shape(parent)
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
