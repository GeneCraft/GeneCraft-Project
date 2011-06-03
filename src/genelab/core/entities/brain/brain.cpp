#include "brain.h"
#include "brainpluggrid.h"


namespace GeneLabCore {
    Brain::Brain(int plugGridSize, QObject *parent) :
        QObject(parent)
    {
        this->plugGrid = new BrainPlugGrid(plugGridSize);
    }

    Brain::Brain(QVariant data) {
        int size = data.toMap()["plugGridSize"].toInt();
        this->plugGrid = new BrainPlugGrid(size);
    }

    QVariant Brain::serialize() {
        QVariantMap data;
        data.insert("plugGridSize", this->plugGrid->getSize());
        return data;
    }
}
