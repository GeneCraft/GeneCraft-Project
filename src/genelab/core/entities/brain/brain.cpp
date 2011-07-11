#include "brain.h"
#include "brainpluggrid.h"
#include "tools.h"
#include "qmath.h"

namespace GeneLabCore {
    Brain::Brain(int plugGridSize, QObject *parent) :
        QObject(parent)
    {
        this->plugGrid = new BrainPlugGrid(plugGridSize);
        this->frequency = qrand()%10 + 1;
    }

    Brain::Brain(QVariant data) {
        int size = data.toMap()["plugGridSize"].toInt();
        this->plugGrid = new BrainPlugGrid(size);
        bool ok = false;
        this->frequency = data.toMap()["frequency"].toInt(&ok);
        if(!ok) {
            frequency = 6; // 10 per sec
        }
    }

    QVariant Brain::serialize() {
        QVariantMap data;
        data.insert("plugGridSize", this->plugGrid->getSize());
        data.insert("frequency", this->frequency);
        return data;
    }

    int Brain::randomPlugGridSize()
    {
        return pow(2,Tools::random(1,6));
    }
}
